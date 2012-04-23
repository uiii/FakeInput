project "FakeInput"
    kind "SharedLib"
    language "C++"

    targetdir "../lib"

    configuration { "linux or bsd or solaris" }
        require_pkg_config()
        require_pkg("x11")
        require_pkg("xtst")
        files {
            "display_unix.cpp",
            "key_unix.cpp",
            "keyboard_unix.cpp",
            "mapper_unix.cpp",
            "mouse_unix.cpp",
            "system_unix.cpp"
        }

    includedirs { "./" }
    includedirs { "../include/FakeInput" }

    files {
        "actions/actionsequence.cpp",
        "actions/commandaction.cpp",
        "actions/keyaction.cpp",
        "actions/mouseaction.cpp",
        "actions/waitaction.cpp",
        "key_base.cpp",
        "keyboard.cpp"
    }
