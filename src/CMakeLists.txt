set(SRCS_COMMON
    key_base.cpp
    keyboard.cpp
    actions/actionsequence.cpp
    actions/commandaction.cpp
    actions/keyaction.cpp
    actions/mouseaction.cpp
    actions/waitaction.cpp
)

set(SRCS_UNIX
    display_unix.cpp
    mouse_unix.cpp
    mapper_unix.cpp
    system_unix.cpp
    keyboard_unix.cpp
    key_unix.cpp
)

set(SRCS_WIN
    mouse_win.cpp
    mapper_win.cpp
    system_win.cpp
    keyboard_win.cpp
    key_win.cpp
)

if(${UNIX})
    set(SRCS
        ${SRCS_COMMON}
        ${SRCS_UNIX}
    )

    set(LIBS
        ${X11_LIBRARIES}
        ${XTest_LIBRARIES}
    )
endif(${UNIX})

if(${WIN32})
    set(SRCS
        ${SRCS_COMMON}
        ${SRCS_WIN}
    )
endif(${WIN32})

if(${TEST_APP})
    set(LIBS ${QT_LIBRARIES} ${LIBS})
endif(${TEST_APP})

add_library(fakeInputStatic STATIC ${SRCS})
target_link_libraries(fakeInputStatic ${LIBS})
set_target_properties(fakeInputStatic
    PROPERTIES
        OUTPUT_NAME fakeInput
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin/lib
)

add_library(fakeInputShared SHARED ${SRCS})
target_link_libraries(fakeInputShared ${LIBS})
set_target_properties(fakeInputShared
    PROPERTIES
        OUTPUT_NAME fakeInput
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin/lib
)
