set(SRCS_COMMON
    key.cpp
    keyboard.cpp
)

set(SRCS_UNIX
    display_unix.cpp
    mouse_unix.cpp
    mapper_unix.cpp
    command_unix.cpp
)

set(SRCS_WIN
    mouse_win.cpp
    mapper_win.cpp
    command_win.cpp
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
