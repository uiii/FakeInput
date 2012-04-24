require "config/premake4/functions"
require "config/premake4/qt-support"

solution "FakeInput"
    configurations { "Debug", "Release" }

    flags { "ExtraWarnings" }

    configuration { "linux or bsd or solaris" }
        defines { "UNIX" }

    configuration { "windows" }
        defines { "WINDOWS" }

    configuration { "linux", "gmake" }
        buildoptions { "-std=c++0x" }

    configuration "Debug"
        defines { "DEBUG" }
        flags { "Symbols" }

    configuration "Release"
        flags { "Optimize" }

    newoption {
        trigger = "test-app",
        description = "Build test applications (requires Qt4)"
    }

    include "src"

    if _OPTIONS["test-app"] then
        include "test"
    end
