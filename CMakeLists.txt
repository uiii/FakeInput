cmake_minimum_required(VERSION 2.8)

project(FakeInput)

find_package(Qt4)
find_package(PkgConfig REQUIRED)

pkg_check_modules(X11 REQUIRED x11)
pkg_check_modules(XTest REQUIRED xtst)

if(${QT_FOUND})
    option(WC_QT_SUPPORT "Build with Qt support" on)
else(${QT_FOUND})
    set(WC_QT_SUPPORT off)
    set(WC_QT_SUPPORT_MESSAGE ": MISSING DEPENDENCY (intall Qt4 library)")
endif(${QT_FOUND})

include(${CMAKE_HOME_DIRECTORY}/aux/cmake/CMakeMacros.txt) # include macros defined for this project
include(${QT_USE_FILE})

include_directories(${CMAKE_HOME_DIRECTORY}/src)
link_directories(${CMAKE_HOME_DIRECTORY}/bin/lib)

if(EXISTS ${CMAKE_HOME_DIRECTORY}/Doxyfile)
    add_custom_target(doxygen ALL
            COMMAND doxygen ${CMAKE_HOME_DIRECTORY}/Doxyfile
    )
else(EXISTS ${CMAKE_HOME_DIRECTORY}/Doxyfile)
    message(WARNING "Doxyfile doesn't exists - doxygen documentation won't be generated")
endif(EXISTS ${CMAKE_HOME_DIRECTORY}/Doxyfile)

configure_file(
    ${CMAKE_HOME_DIRECTORY}/src/config.h.cmake
    ${PROJECT_BINARY_DIR}/src/config.h
)

include_directories(${PROJECT_BINARY_DIR}/src)

add_subdirectory(src)
add_subdirectory(test)

message(STATUS "")
message(STATUS "OPTIONS: (to change it: -D<option>=<ON|OFF>)")
message(STATUS "")
message(STATUS "Build with Qt support (WC_QT_SUPPORT) ... ${WC_QT_SUPPORT}${WC_QT_SUPPORT_MESSAGE}")
message(STATUS "")
