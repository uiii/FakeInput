# headers
set(HDRS_COMMON
    key.hpp
    key_base.hpp
    keyboard.hpp
    mapper.hpp
    mouse.hpp
    system.hpp
    types.hpp
    actions/actions.hpp
    actions/action.hpp
    actions/actionsequence.hpp
    actions/commandaction.hpp
    actions/keyaction.hpp
    actions/mouseaction.hpp
    actions/waitaction.hpp
)

set(HDRS_UNIX
    display_unix.hpp
    key_unix.hpp
)

set(HDRS_WIN
    key_win.hpp
)

# sources
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
    set(HDRS
        ${HDRS_COMMON}
        ${HDRS_UNIX}
    )

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
    set(HDRS
        ${HDRS_COMMON}
        ${HDRS_WIN}
    )

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
        VERSION ${VERSION}.${SUBVERSION}.0
        SOVERSION ${VERSION}
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin/lib # needed on Unix
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin/lib # needed on Windows
)

install(TARGETS fakeInputStatic fakeInputShared
    ARCHIVE DESTINATION ${INSTALL_PREFIX}/${INSTALL_LIBRARY_DIR}
    LIBRARY DESTINATION ${INSTALL_PREFIX}/${INSTALL_LIBRARY_DIR}
    RUNTIME DESTINATION ${INSTALL_PREFIX}/${INSTALL_LIBRARY_DIR}
)

install(FILES fakeinput.hpp
    DESTINATION ${INSTALL_PREFIX}/${INSTALL_HEADER_DIR}
)

install(FILES ${HDRS}
    DESTINATION ${INSTALL_PREFIX}/${INSTALL_HEADER_DIR}/fakeinput
)
