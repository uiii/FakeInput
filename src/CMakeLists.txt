set(SRCS
    key.cpp
    keyboard.cpp
    mouse.cpp
    command.cpp
    display_unix.cpp
)

if(${UNIX})
    set(LIBS
        ${X11_LIBRARIES}
        ${XTest_LIBRARIES}
    )
endif(${UNIX})

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
