--
-- qt-support.lua
-- Support for Qt Framework for Premake
-- Copyright (c) 2011 Konstantin Tokarev
--
-- Version 1.0
--
-- Known limitations:
--      only gmake
--      on Mac OS X only framework configuration of Qt is supported
--      the next Qt modules are not supported:
--        ActiveQt
--        QtDBus
--        QtDesigner
--        Phonon
--

local _s = string.format

premake.qt = {}

-- New dirs needed for intermediate files
premake.qt.artifactdirs = {}
premake.qt.mocexcludefromsources = {}

--
-- Helper functions
--

function premake.qt.massinsert(t, ...)
    t = t or {}
    for _,v in ipairs {...} do
        table.insert(t, v)
    end
end

function premake.qt.joinTables(t1, t2)
    for k,v in ipairs(t2) do
        table.insert(t1, v)
    end
    return t1
end

function premake.qt.dedup(t)
    unique = {}
    for _, v in ipairs(t) do
        if not table.contains(unique, v) then
            table.insert(unique, v)
        end
    end
    t = nil
    return unique
end

function premake.qt.concatif(predicate, list, sep)
    local t = {}
    for _,v in ipairs(list) do
        if predicate(v) then
            table.insert(t, v)
        end
    end
    return table.concat(t, sep)
end

function premake.qt.gettoolname(cfg)
    if _OPTIONS.cc then
        return _OPTIONS.cc
    end
    local action = premake.action.current()
    if action.valid_tools then
        return action.valid_tools.cc[1]
    end
    return "gcc"
end

-- function premake.qt.isstaticlibrary(fname)
--     local ext = path.getextension(fname):lower()
--     if os.is("windows") and ext == ".lib" then
--         return true
--     end
--     return ext == ".a"
-- end
-- 
-- function premake.qt.issharedlibrary(fname)
--     local ext = path.getextension(fname):lower()
--     if os.is("windows") and ext == ".dll" then -- Not sure if it will work for Qt
--         return true
--     end
--     if os.is("macosx") and ext == ".dylib" then
--         return true
--     end
--     return ext == ".so"
-- end

function premake.qt.safeopen(fname, mode)
    local f, err = io.open(fname, mode)
    if not f then
        error(err, 2)
    end
    return f
end

--
-- This table contains "type detector" functions as keys,
-- and lists of code generation callbacks as values
--
premake.qt.codegencallbacks = {}

function premake.qt.registercodegenerator(typedetector, generator)
    if not premake.qt.codegencallbacks[typedetector] then
        premake.qt.codegencallbacks[typedetector] = {}
    end
    table.insert(premake.qt.codegencallbacks[typedetector], generator)
end

--
-- Type detectors
--

function premake.qt.ismocableheader(fname)
    if not path.iscppheader(fname) then
        return false
    end
    local f = premake.qt.safeopen(fname)
    for line in f:lines(fname) do
        if line:find("Q_OBJECT") then
--            print("Mocable: "..fname)
            io.close(f)
            return true
        end
    end
    io.close(f)
    return false
end

function premake.qt.ismocablecppfile(fname)
    if not path.iscppfile(fname) then
        return false
    end
    local f = premake.qt.safeopen(fname)
    for line in f:lines(fname) do
        if line:find("#%s*include%s*\""..path.getbasename(fname).."%.moc\"") then
--            print("Mocable: "..fname)
            io.close(f)
            return true
        end
    end
    io.close(f)
    return false
end

-- Workaround for dirty trick, need to private slots working:
--     C++ file includes moc_xxx.cpp, generated for its header
function premake.qt.cppincludesmoc(fname)
    if not path.iscppfile(fname) then
        return false
    end
    local f = premake.qt.safeopen(fname)
    local cpp = f:read("*a")
    -- TODO: Don't hardcode "moc_", ".cpp", "$(MOCDIR)/"
    -- TODO: Don't open the same file twice
    for mocfile in cpp:gmatch("#%s-include%s-\"(moc_%w-.cpp)") do
        print(fname .. " includes " .. mocfile)
        table.insert(premake.qt.mocexcludefromsources, "$(MOCDIR)/" .. mocfile)
    end
    io.close(f)
    return false
end

--Test
--local lines = { "#include \"abc.moc\"", "#     include \"abc.moc\"", "#include abc.moc", "#include \"abc_moc\"" }
--for _,v in ipairs(lines) do
--    if v:find("#%s*include%s*\""..path.getbasename("src/abc.cpp").."%.moc\"") then
--        print "Mocable"
--    else
--        print "Not mocable"
--    end
--end
--

function premake.qt.typematcher(extension)
    return function(fname)
        local ext = path.getextension(fname):lower()
        return ext == extension
    end
end

premake.qt.isuifile = premake.qt.typematcher(".ui")
premake.qt.isqrcfile = premake.qt.typematcher(".qrc")
premake.qt.istsfile = premake.qt.typematcher(".ts")



-- Callbacks for code generation
-- @param footer Table containing generated lines of Makefile
-- @param file Current file from project for which code should be generated

function premake.qt.moc(footer, fileprj, filepath)
    local moc_source = _s('$(MOCDIR)/moc_%s.cpp',  _MAKE.esc(path.getbasename(fileprj)))
    table.insert(footer, _s('%s: %s', moc_source, _MAKE.esc(fileprj)))
    table.insert(footer, '\t@echo moc '..path.getname(fileprj))
    table.insert(footer, '\t$(SILENT) $(QTMOC) $(MOCFLAGS) -nw -o "$@" "$<"')
    return moc_source
end

function premake.qt.moc_i(footer, fileprj, filepath)
    local moc_source = _s('$(MOCDIR)/%s.moc',  _MAKE.esc(path.getbasename(fileprj)))
    table.insert(footer, _s('%s: %s', moc_source, _MAKE.esc(fileprj)))
    table.insert(footer, '\t@echo moc '..path.getname(fileprj))
    table.insert(footer, '\t$(SILENT) $(QTMOC) $(MOCFLAGS) -i -o "$@" "$<"')
    return moc_source
end

function premake.qt.ui_depends(filepath)
    -- Iterator splits output of uic -d line by line
    return string.gmatch(os.outputof("uic -d " .. filepath) or "", "(.-)\n")
end

function premake.qt.uic(footer, fileprj, filepath)
    local ui_header = _s('$(UIDIR)/ui_%s.h',  _MAKE.esc(path.getbasename(fileprj)))
    local target = { _s('%s: %s', ui_header, _MAKE.esc(fileprj)) }
    for dep in premake.qt.ui_depends(filepath) do
        table.insert(target, " \\\n "..path.join(path.getdirectory(fileprj), dep))
    end
    table.insert(footer, table.concat(target))
    table.insert(footer, '\t@echo uic '..path.getbasename(fileprj))
    table.insert(footer, '\t$(SILENT) $(QTUIC) "$<" -o "$@"')
    return ui_header
end

function premake.qt.qrc_depends(filepath)
    local qrcfile = premake.qt.safeopen(filepath)
    local qrc = qrcfile:read("*a")
    return string.gmatch(qrc, "<file[^>]*>([^<]+)</file>")
end

function premake.qt.rcc(footer, fileprj, filepath)
    local qrc_source = _s('$(RCCDIR)/qrc_%s.cpp',  _MAKE.esc(path.getbasename(fileprj)))
    local target = { _s('%s: %s', qrc_source, _MAKE.esc(fileprj)) }
    for dep in premake.qt.qrc_depends(filepath) do
        table.insert(target, " \\\n "..path.join(path.getdirectory(fileprj), dep))
    end
    table.insert(footer, table.concat(target))
    table.insert(footer, '\t@echo rcc '..path.getname(fileprj))
    table.insert(footer, '\t$(SILENT) $(QTRCC) -name '.._MAKE.esc(path.getbasename(fileprj))..' -o "$@" "$<"')
    return qrc_source
end

function premake.qt.lrelease(footer, fileprj, filepath)
    local qm_file = _s('$(QMDIR)/%s.qm',  _MAKE.esc(path.getbasename(fileprj)))
    table.insert(footer, _s('%s: %s', qm_file, _MAKE.esc(fileprj)))
    table.insert(footer, '\t@echo lrelease '..path.getbasename(fileprj))
    table.insert(footer, '\t$(SILENT) $(QTLRELEASE) "$<" -qm "$@"')
    return qm_file
end

-- Register callbacks
premake.qt.registercodegenerator(premake.qt.ismocableheader, premake.qt.moc)
premake.qt.registercodegenerator(premake.qt.ismocablecppfile, premake.qt.moc_i)
premake.qt.registercodegenerator(premake.qt.cppincludesmoc, function() end)
premake.qt.registercodegenerator(premake.qt.isuifile, premake.qt.uic)
premake.qt.registercodegenerator(premake.qt.isqrcfile, premake.qt.rcc)
premake.qt.registercodegenerator(premake.qt.istsfile, premake.qt.lrelease)

-- Write Makefile rules for code generation
function premake.qt.writecodegenrules(prj)
    local footer = {}
    prj.qt_generated_files = prj.qt_generated_files or {}
    prj.qt_generated_files_keys = prj.qt_generated_files_keys or {}

    for _,file in ipairs(prj.files) do
        -- Exclude generated files from code generation
        if not prj.qt_generated_files_keys[file] then
            -- Iterate over premake.qt.codegencallbacks
            -- If some of registered type detectors returns true on the file,
            -- run all associated callbacks
            local filewithpath = path.rebase(file, prj.location, os.getcwd())
            for typedetector,generators in pairs(premake.qt.codegencallbacks) do
                if typedetector(filewithpath) then
                    for _,generator in ipairs(generators) do
                        local outfilename = generator(footer, file, filewithpath)
                        table.insert(prj.files, outfilename)
                        table.insert(prj.qt_generated_files, outfilename)
                        prj.qt_generated_files_keys[outfilename] = true
                    end
                end
            end
        end
    end
    table.insert(footer, "\n")
    table.insert(footer, "prebuild: $(QT_DIRS) "
        .. table.concat(prj.qt_generated_files, " \\\n "))
    premake.qt.joinTables(prj.makeprjfooter, footer)
end

-- Find Qt4 and set up additional Makefile rules
function premake.qt.useqt(prj)
    if prj.use_qt_guard then
        return
    end
    prj.use_qt_guard = true

    --
    --We use the next Qt search strategy:
    --1. qtdir in project configuration
    --2. first $(QMAKE) executable in PATH
    --Maybe we should allow using of pkg-config for it.
    --
    local qmake = _OPTIONS["qt-qmake"] or "qmake"
    premake.qt.massinsert(prj.makeprjheader,
        "QMAKE ?= " .. qmake,
        "QT_BIN_DEFAULT     := $(shell $(QMAKE) -query QT_INSTALL_BINS)",
        "QT_LIB_DEFAULT     := $(shell $(QMAKE) -query QT_INSTALL_LIBS)",
        "QT_INCLUDE_DEFAULT := $(shell $(QMAKE) -query QT_INSTALL_HEADERS)",
        "QT_PLUGINS_DEFAULT := $(shell $(QMAKE) -query QT_INSTALL_PLUGINS)"
        -- Do we need mkspecs, other stuff?
    )

    premake.qt.artifactdirs = premake.qt.dedup(premake.qt.artifactdirs)
    table.insert(prj.makeprjfooter, "$(QT_DIRS):")
    table.insert(prj.makeprjfooter, "ifeq (posix,$(SHELLTYPE))")
    for _, dir in ipairs(premake.qt.artifactdirs) do
        table.insert(prj.makeprjfooter, "\t$(SILENT) mkdir -p " .. dir)
    end
    table.insert(prj.makeprjfooter, "else")
    for _, dir in ipairs(premake.qt.artifactdirs) do
        table.insert(prj.makeprjfooter, _s('\t$(SILENT) mkdir $(subst /,\\\\,%s)', dir))
    end
    table.insert(prj.makeprjfooter, "endif")
    table.insert(prj.makeprjfooter, "")

    table.insert(prj.makeprjfooter, ".PHONY: lupdate")
    table.insert(prj.makeprjfooter, "lupdate:")
    if premake.qt.concatif(premake.qt.istsfile, prj.files, "") ~= "" then
        premake.qt.massinsert(prj.makeprjfooter,
        _s("\t$(QTLUPDATE) $(INCLUDES) \\\n  %s \\\n  -ts \\\n  %s",
            premake.qt.concatif(function(f)
                return path.iscppfile(f) or path.iscppheader(f) or premake.qt.isuifile(f)
            end,
            prj.files, " \\\n  "),
            premake.qt.concatif(premake.qt.istsfile, prj.files, " \\\n  "))
        )
    end
    table.insert(prj.makeprjfooter, "")

    prj.makeprjclean = prj.makeprjclean or {}
    -- QMDIR may be equal TARGETDIR which is not removed
    table.insert(prj.makeprjclean, 'ifeq (posix,$(SHELLTYPE))')
    table.insert(prj.makeprjclean, '\t$(SILENT) rm -rf $(QT_DIRS)')
    table.insert(prj.makeprjclean, 'else')
    -- Probably will fail on Widows - foreach?
    table.insert(prj.makeprjclean, '\t$(SILENT) if exist $(subst /,\\\\,$(QT_DIRS)) rmdir /s /q $(subst /,\\\\,$(QT_DIRS))')
    table.insert(prj.makeprjclean, 'endif')

--    print("Uses Qt!")
end

--
-- Adds variable @a varname with value @value to Makefile
--
function premake.qt.makevariable(cfg, varname, value)
    cfg.qt_vars = cfg.qt_vars or {}
    if not table.contains(cfg.qt_vars, varname) then
        table.insert(cfg.makeprjconfig, varname.. " = "..value)
        table.insert(cfg.qt_vars, varname)
    end
end


-- Merge with useqt?
function premake.qt.useqtcore(cfg)
    if cfg.use_qt_core_guard then
        return
    end
    cfg.use_qt_core_guard = true

    -- Typically, Qt is installed in the next layout:
    -- "QTDIR"/
    --          bin/
    --          include/
    --          lib/
    --          mkspecs/
    --          ...
    -- Linux distros can shuffle stuff randomly, but QTDIR with
    -- proper symlinks usually exists.
    --
    -- AFAIK single exception is Qt Mac installation done by installer
    --

    if cfg.qtdir then
        premake.qt.makevariable(cfg, "QTDIR", cfg.qtdir)
        premake.qt.makevariable(cfg, "QT_BIN", "$(QTDIR)/bin")
        premake.qt.makevariable(cfg, "QT_INCLUDE", "$(QTDIR)/include")
        premake.qt.makevariable(cfg, "QT_LIB", "$(QTDIR)/lib")
        premake.qt.makevariable(cfg, "QT_PLUGINS", "$(QTDIR)/plugins")
    else
        premake.qt.makevariable(cfg, "QT_BIN", "$(QT_BIN_DEFAULT)")
        premake.qt.makevariable(cfg, "QT_INCLUDE", "$(QT_INCLUDE_DEFAULT)")
        premake.qt.makevariable(cfg, "QT_LIB", "$(QT_LIB_DEFAULT)")
        premake.qt.makevariable(cfg, "QT_PLUGINS", "$(QT_PLUGINS_DEFAULT)")
    end
    premake.qt.makevariable(cfg, "QTMOC", "$(QT_BIN)/moc")
    premake.qt.makevariable(cfg, "QTUIC", "$(QT_BIN)/uic")
    premake.qt.makevariable(cfg, "QTRCC", "$(QT_BIN)/rcc")
    premake.qt.makevariable(cfg, "QTLUPDATE", "$(QT_BIN)/lupdate")
    premake.qt.makevariable(cfg, "QTLRELEASE", "$(QT_BIN)/lrelease")
    premake.qt.makevariable(cfg, "MOCDIR", cfg.mocdir or "$(OBJDIR)")
    premake.qt.makevariable(cfg, "UIDIR", cfg.uidir or "$(OBJDIR)")
    premake.qt.makevariable(cfg, "RCCDIR", cfg.rccdir or "$(OBJDIR)")
    premake.qt.makevariable(cfg, "QMDIR", cfg.qmdir or "$(TARGETDIR)")
    if cfg.mocdir then
        table.insert(premake.qt.artifactdirs, "$(MOCDIR)")
        table.insert(cfg.makeprjconfig, "QT_DIRS += $(MOCDIR)")
    end
    if cfg.uidir then
        table.insert(premake.qt.artifactdirs, "$(UIDIR)")
        table.insert(cfg.makeprjconfig, "QT_DIRS += $(UIDIR)")
    end
    if cfg.rccdir then
        table.insert(premake.qt.artifactdirs, "$(RCCDIR)")
        table.insert(cfg.makeprjconfig, "QT_DIRS += $(RCCDIR)")
    end
    if cfg.qmdir then
        table.insert(premake.qt.artifactdirs, "$(QMDIR)")
        table.insert(cfg.makeprjconfig, "QT_DIRS += $(QMDIR)")
    end

    if os.is("macosx") then
        premake.qt.makevariable(cfg, "MOCFLAGS", "$(INCLUDES) $(DEFINES) -D__APPLE__ -D__GNUC__")
    else
        premake.qt.makevariable(cfg, "MOCFLAGS", "$(INCLUDES) $(DEFINES)")
    end

    premake.qt.massinsert(cfg.includedirs,
        "$(QT_INCLUDE)",
        "$(UIDIR)",
        "$(MOCDIR)"
    )
    table.insert(cfg.libdirs, "$(QT_LIB)")
    if os.is("macosx") then
        table.insert(cfg.linkoptions, "-F$(QT_LIB)")
    end
    -- Add rpath
    if not os.is("windows") and not os.is("macosx") then
        table.insert(cfg.defines, "_REENTRANT")
        premake.qt.massinsert(cfg.linkoptions, "-Wl,-rpath,$(QT_LIB)", "-lpthread")
    end

    if os.is("windows") then
        premake.qt.massinsert(cfg.defines,
            "UNICODE",
            "WIN32",
            "QT_LARGEFILE_SUPPORT",
            "QT_THREAD_SUPPORT"
        )

        -- From QMake spec win32-g++:
        --
        -- QMAKE_LINK_OBJECT_MAX = 10
        -- QMAKE_LINK_OBJECT_SCRIPT= object_script
        --
        if premake.qt.gettoolname(cfg) == "gcc" then
            premake.qt.massinsert(cfg.linkoptions,
                "-enable-stdcall-fixup",
                "-Wl,-enable-auto-import",
                "-Wl,-enable-runtime-pseudo-reloc"
            )
            -- QtMain
            if cfg.kind == "ConsoleApp" or cfg.kind == "WindowedApp" then
                table.insert(cfg.defines, "QT_NEEDS_QMAIN")
                -- Insert mingw32 and qtmain before any Qt library
                table.insert(cfg.links, 1, "mingw32")
                table.insert(cfg.links, 2, "qtmain")
            end
            if not cfg.flags.NoExceptions then
                table.insert(cfg.linkoptions, "-mthreads")
            end
        end
    end

    --  Waiting for proper os.findlib to search custom paths and static libs
    --    if cfg.qtdir and os.findlib("QtCore", path.join(cfg.qtdir, "lib") ...
    if _OPTIONS["qt-static"] or cfg.flags.QtStatic then
        -- Link plugins
        for dir, plugins in pairs(cfg.qtplugins) do
            for _, plugin in ipairs(plugins) do
                table.insert(cfg.libdirs, "$(QT_PLUGINS)/" .. dir)
                if os.is("windows") then
                    if premake.config.isdebugbuild(cfg) then
                        table.insert(cfg.links, plugin .. "d")
                    else
                        table.insert(cfg.links, plugin)
                    end
                else
                    table.insert(cfg.links, plugin)
                end
            end
        end
    else
        if os.is("windows") then
            table.insert(cfg.defines, "QT_DLL")
        else
            table.insert(cfg.defines, "QT_SHARED")
        end
    end

    -- QT_NO_DEBUG
    if premake.config.isoptimizedbuild(cfg.flags) then
        table.insert(cfg.defines, "QT_NO_DEBUG")
    end

    --
    -- Qt Plugins
    --
    if cfg.flags.QtPlugin then
        if cfg.kind == "StaticLib" then
            premake.qt.massinsert(cfg.defines, "QT_STATICPLUGIN", "QT_PLUGIN")
        elseif cfg.kind == "SharedLib" then
            table.insert(cfg.defines, "QT_PLUGIN")
        else
            error("Invalid project kind " .. cfg.kind .. " for Qt plugin")
        end
    end
end

--
-- Qt modules
--

local qt_modules = {
    Qt =
    {
        depends = { }
    },
    QtCore =
    {
        define = "QT_CORE_LIB",
        winlinks = { "kernel32", "user32", "shell32", "uuid", "ole32", "advapi32", "ws2_32" }
    },
    QtGui =
    {
        depends = { "QtCore" },
        define = "QT_GUI_LIB",
        winlinks = { "gdi32", "comdlg32", "oleaut32", "imm32", "winmm", "winspool",
                     "ws2_32", "ole32", "uuid", "user32", "advapi32" }
    },
    QtDeclarative =
    {
        depends = { "QtCore", "QtGui" },
        define = "QT_DECLARATIVE_LIB",
    },
    QtHelp =
    {
        depends = { "QtCore", "QtSql", "QtXml" }
    },
    QtMultimedia =
    {
        depends = { "QtCore", "QtGui" },
        define = "QT_MULTIMEDIA_LIB",
    },
    QtNetwork =
    {
        depends = { "QtCore" },
        define = "QT_NETWORK_LIB"
    },
    QtOpenGL =
    {
        depends = { "QtCore", "QtGui" },
        define = "QT_OPENGL_LIB",
        -- Should OpenGL libs be a part of platform configuration?
        links = { "GLU", "GL" }, -- GL ES?
        maclinks = { "OpenGL.framework", "AGL.framework" },
        winlinks = { "glu32", "opengl32", "gdi32", "user32" }
    },
    QtOpenVG =
    {
        -- Untested, may require something else
        depends = { "QtCore", "QtGui" },
        define = "QT_OPENVG_LIB",
        links = { "OpenVG" }
    },
    QtScript =
    {
        depends = { "QtCore" },
        define = "QT_SCRIPT_LIB",
    },
    QtScriptTools =
    {
        depends = { "QtCore", "QtGui", "QtScript" },
        define = "QT_SCRIPTTOOLS_LIB",
    },
    QtSql =
    {
        depends = { "QtCore" },
        define = "QT_SQL_LIB",
    },
    QtSvg =
    {
        depends = { "QtCore", "QtGui" },
        define = "QT_SVG_LIB",
    },
    QtTest =
    {
        depends = { "QtCore" }
    },
    QtUiTools =
    {
        depends = { "QtCore", "QtXml" }
    },
    QtXml =
    {
        depends = { "QtCore" },
        define = "QT_XML_LIB"
    },
    QtXmlPatterns =
    {
        depends = { "QtCore" },
        define = "QT_XMLPATTERNS_LIB"
    },
    QtWebKit =
    {
        depends = { "QtCore", "QtGui", "QtNetwork" },
        define = "QT_WEBKIT_LIB"
    },
    Qt3Support =
    {
        depends = { "QtCore" },
        define = "QT_QT3SUPPORT_LIB"
    }
}

--local qt_modules_lower = {}
--for name, _ in pairs(qt_modules) do
--    local lowername = name:lower()
--    table.insert(qt_modules_lower, lowername)
--end

--
-- Add necessary includedirs, defines, and links for used Qt modules
--

function premake.qt.usemodule(cfg, moduleName, moduleDefines)
    if os.is("macosx") then
        local fwname = moduleName..".framework"
        local fwheaders = path.join(fwname, "Headers")
        table.insert(cfg.links, fwname)
        table.insert(cfg.includedirs, path.join("$(QT_LIB)", fwheaders))
    elseif os.is("windows") then
        if _OPTIONS["qt-static"] or cfg.flags.QtStatic then
            if premake.config.isdebugbuild(cfg) then
                table.insert(cfg.links, moduleName .. "d")
            else
                table.insert(cfg.links, moduleName)
            end
        else
            if premake.config.isdebugbuild(cfg) then
                table.insert(cfg.links, moduleName .. "d4")
            else
                table.insert(cfg.links, moduleName .. "4")
            end
        end
    else
        table.insert(cfg.links, moduleName)
    end
    table.insert(cfg.includedirs, "$(QT_INCLUDE)/" .. moduleName)
    if moduleDefines then
        table.insert(cfg.defines, moduleDefines)
    end
    if moduleName == "QtCore" then
        premake.qt.useqtcore(cfg)
    end
--    print("Uses "..moduleName.."!")
end

function premake.qt.checkmodulename(value)
    local lowervalue = value:lower()
    for v, _ in pairs(qt_modules) do
        if lowervalue == v:lower() then
            return v
        end
    end
    if lowervalue:startswith("qt") then
        return nil, "Invalid Qt module " .. value
    end

    -- 3rd party use - give back as is
    return value
end

function premake.qt.runuses(cfg)
    for _,u in ipairs(cfg.uses) do
        local mod = qt_modules[u]
        if mod then
            premake.qt.usemodule(cfg, u, mod.define)
            if os.is("windows") and mod.winlinks then
                premake.qt.joinTables(cfg.links, mod.winlinks)
            elseif os.is("macosx") and mod.maclinks then
                premake.qt.joinTables(cfg.links, mod.maclinks)
            elseif mod.links then
                premake.qt.joinTables(cfg.links, mod.links)
            end
        end
    end
end


newaction {
    trigger    = "qt",
    isinternal = true,

    onsolution = function(sln)
        -- lupdate proxy-target
        sln.makeslnfooter = sln.makeslnfooter or {}
        table.insert(sln.makeslnfooter, "lupdate:")
        for _ ,prj in ipairs(sln.projects) do
            table.insert(sln.makeslnfooter,
                _s('\t@${MAKE} --no-print-directory -C %s -f %s lupdate',
                _MAKE.esc(path.getrelative(sln.location, prj.location)),
                _MAKE.esc(_MAKE.getmakefilename(prj, true))))
        end
        table.insert(sln.makeslnfooter, "")
    end,

    onproject = function(prj)
        local cc = premake.gettool(prj)
        local platforms = premake.filterplatforms(prj.solution, cc.platforms, "Native")
        local isQtProject = false
        for _, platform in ipairs(platforms) do
            for cfg in premake.eachconfig(prj, platform) do
                cfg.links = cfg.links or {}
                cfg.includedirs = cfg.includedirs or {}
                cfg.defines = cfg.defines or {}
                cfg.linkoptions = cfg.linkoptions or {}

                -- Detect Qt use, insert module dependencies
                local canonicUses = {}
                for _, use in ipairs(cfg.uses) do
                    local u, err = premake.checkvalue(use, premake.qt.checkmodulename)
                    if u then
                        local m = qt_modules[u]
                        if m then
                            isQtProject = true
                            for _, dep in ipairs(m.depends) do
                                table.insert(canonicUses, dep)
                            end
                        end
                        if u ~= "Qt" then
                            table.insert(canonicUses, u)
                        end
                    else
                        error(err)
                    end
                end
                cfg.uses = canonicUses
            end

            -- Configuration block of Makefile
            if isQtProject then
                for cfg in premake.eachconfig(prj, platform) do
                    table.insert(cfg.uses, "QtCore")
                    if prj.kind == "WindowedApp" then
                        table.insert(cfg.uses, "QtGui")
                    end
                    cfg.uses = premake.qt.dedup(cfg.uses)

                    premake.qt.runuses(cfg)

                    cfg.includedirs = premake.qt.dedup(cfg.includedirs)
                    cfg.defines = premake.qt.dedup(cfg.defines)
                    cfg.libdirs = premake.qt.dedup(cfg.libdirs)
                    cfg.links = premake.qt.dedup(cfg.links)
                    cfg.linkoptions = premake.qt.dedup(cfg.linkoptions)
                end
                premake.qt.useqt(prj)
            end
        end

        -- Makefile footer
        premake.qt.writecodegenrules(prj)

        -- TODO: Think how to do this post-exclude properly (and when)
        local files = {}
        for _, fname in ipairs(prj.files) do
            local excluded = false
            for _, exclude in ipairs(premake.qt.mocexcludefromsources) do
                print(fname)
                excluded = (fname == exclude)
                if excluded then
                    print("Excluding " .. fname .. " from sources")
                    break
                end
                --prj.sources
            end
            if not excluded then
                table.insert(files, fname)
            end
        end
        prj.files = files
    end
}

--
-- Inject our code after baking but before gmake action
--

premake.action.adddependency("gmake", "qt")

--
-- Public Qt-specific API (tries to be consistent with QMake)
--
newapis {
    -- Root of Qt installation
    qtdir =
    {
        kind = "path",
        scope = "config"
    },

    -- Directory where moc_*.cpp and *.moc files are written (by default objdir)
    mocdir =
    {
        kind = "path",
        scope = "config"
    },

    -- Directory where ui_*.h files are written (by default objdir)
    uidir =
    {
        kind = "path",
        scope = "config"
    },

    -- Directory where qrc_*.cpp files are written (by default objdir)
    rccdir =
    {
        kind = "path",
        scope = "config"
    },

    -- Directory where *.qm files are written (by default targetdir)
    qmdir =
    {
        kind = "path",
        scope = "config"
    },

    -- List of used Qt plugins: keys - plugin directories (e.g., "imageformats"),
    -- values - plugin names (e.g., "qgif")
    qtplugins =
    {
        kind = "keyvalue",
        scope = "config"
    }
}

premake.newflag "QtPlugin"
premake.newflag "QtStatic"

newoption {
    trigger = "qt-qmake",
    value = "path",
    description = "Specify qmake executable to use instead of 'qmake'"
}

newoption {
    trigger = "qt-static",
    description = "Assume Qt is built as static libraries"
}

