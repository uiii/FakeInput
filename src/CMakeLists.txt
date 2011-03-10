set(SRCS
    key.cpp
    keyboard.cpp
    mouse.cpp
    command.cpp
)

set(LIBS
    ${X11_LIBRARIES}
    ${XTest_LIBRARIES}
)

if(${WC_QT_SUPPORT})
    set(WC_LIBS ${QT_LIBRARIES} ${LIBS})
endif(${WC_QT_SUPPORT})

add_library(fakeInputStatic STATIC ${SRCS})
add_library(fakeInputShared SHARED ${SRCS})
target_link_libraries(fakeInputStatic ${LIBS})
target_link_libraries(fakeInputShared ${LIBS})
set_target_properties(fakeInputStatic
    PROPERTIES
        OUTPUT_NAME fakeInput
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin/lib
)

set_target_properties(fakeInputShared
    PROPERTIES
        OUTPUT_NAME fakeInput
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin/lib
)
