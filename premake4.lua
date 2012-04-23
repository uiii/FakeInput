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

    include "src"
    --include "test"
