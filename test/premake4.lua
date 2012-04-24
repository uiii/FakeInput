project "ActionsTest"
    kind "WindowedApp"
    language "C++"

    uses "QtGui"

    targetdir "../bin"
    targetname "actions_test"

    includedirs { "../include/FakeInput" }
    includedirs { "../src" }

    files { "actionsTest/*.hpp" }
    files { "actionsTest/*.cpp" }

    links { "FakeInput" }

project "CommandTest"
    kind "WindowedApp"
    language "C++"

    uses "QtGui"

    targetdir "../bin"
    targetname "command_test"

    includedirs { "../include/FakeInput" }
    includedirs { "../src" }

    files { "commandTest/*.hpp" }
    files { "commandTest/*.cpp" }

    links { "FakeInput" }

project "KeyEventTest"
    kind "WindowedApp"
    language "C++"

    uses "QtGui"

    targetdir "../bin"
    targetname "key_event_test"

    includedirs { "../include/FakeInput" }
    includedirs { "../src" }

    files { "keyEventTest/*.hpp" }
    files { "keyEventTest/*.cpp" }

    links { "FakeInput" }
    links { "X11" }

project "MouseEventTest"
    kind "WindowedApp"
    language "C++"

    uses "QtGui"

    targetdir "../bin"
    targetname "mouse_event_test"

    includedirs { "../include/FakeInput" }
    includedirs { "../src" }

    files { "mouseEventTest/*.hpp" }
    files { "mouseEventTest/*.cpp" }

    links { "FakeInput" }

