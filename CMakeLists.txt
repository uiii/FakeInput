cmake_minimum_required(VERSION 2.8)

project(FakeInput)

set(VERSION 1)
set(SUBVERSION 0)

find_package(Qt4)
find_package(Doxygen)
find_package(PkgConfig REQUIRED)

if(${UNIX})
    pkg_check_modules(X11 REQUIRED x11)
    pkg_check_modules(XTest REQUIRED xtst)
endif(${UNIX})

option(TEST_APP "Build testing applications (Requires Qt)" off)
option(DOC "Generate API documentation (Requires Doxygen)" off)

if(${TEST_APP})
    if(NOT ${QT_FOUND})
        set(TEST_APP off)
        set(TEST_APP_MESSAGE ": MISSING DEPENDENCY (intall Qt4 library)")
    endif(NOT ${QT_FOUND})
endif(${TEST_APP})

if(${DOC})
    if(NOT ${DOXYGEN_FOUND})
        set(DOC off)
        set(DOC_MESSAGE ": MISSING DEPENDENCY (intall Doxygen)")
    endif(NOT ${DOXYGEN_FOUND})
endif(${DOC})

include(${CMAKE_HOME_DIRECTORY}/config/cmake/CMakeMacros.txt) # include macros defined for this project
include(${QT_USE_FILE})

include_directories(${CMAKE_HOME_DIRECTORY}/src)
link_directories(${CMAKE_HOME_DIRECTORY}/bin/lib)

if(${DOC} AND (EXISTS ${CMAKE_HOME_DIRECTORY}/Doxyfile.in))
    file(MAKE_DIRECTORY ${CMAKE_HOME_DIRECTORY}/doc/doxygen)
    configure_file(
        ${CMAKE_HOME_DIRECTORY}/Doxyfile.in
        ${CMAKE_BINARY_DIR}/Doxyfile
        @ONLY
    )
    add_custom_target(doc ALL
            ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/Doxyfile
            WORKING_DIRECTORY ${CMAKE_HOME_DIRECTORY}
            COMMENT "Generating API documentation with Doxygen"
    )
elseif(${DOC} AND (EXISTS ${CMAKE_HOME_DIRECTORY}/Doxyfile.in))
    message(WARNING "Doxyfile.in doesn't exists - doxygen documentation won't be generated")
endif(${DOC} AND (EXISTS ${CMAKE_HOME_DIRECTORY}/Doxyfile.in))

configure_file(
    ${CMAKE_HOME_DIRECTORY}/src/config.hpp.cmake
    ${PROJECT_BINARY_DIR}/src/config.hpp
)

include_directories(${PROJECT_BINARY_DIR}/src)

if("${INSTALL_PREFIX}" STREQUAL "")
    set(INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})
endif("${INSTALL_PREFIX}" STREQUAL "")

if(NOT "${INSTALL_LIBRARY_DIR}")
    set(INSTALL_LIBRARY_DIR "lib")
endif(NOT "${INSTALL_LIBRARY_DIR}")

if(NOT "${INSTALL_HEADER_DIR}")
    set(INSTALL_HEADER_DIR "include")
endif(NOT "${INSTALL_HEADER_DIR}")

install_directory(${INSTALL_PREFIX})
install_directory(${INSTALL_PREFIX}/${INSTALL_LIBRARY_DIR})
install_directory(${INSTALL_PREFIX}/${INSTALL_HEADER_DIR})
install_directory(${INSTALL_PREFIX}/${INSTALL_HEADER_DIR}/fakeinput)

add_subdirectory(src)
set(QT_LIBRARIES ${QT_LIBRARIES} ${QT_QTMAIN_LIBRARY})
add_subdirectory(test)

if(${UNIX})
    install_pkg_config_file(${CMAKE_HOME_DIRECTORY}/fakeinput.pc.in)
endif(${UNIX})

if(${WIN32})
    install_to_win_path(${INSTALL_PREFIX}/${INSTALL_LIBRARY_DIR})
endif(${WIN32})

add_uninstall_target(${CMAKE_HOME_DIRECTORY}/config/cmake)

message(STATUS "")
message(STATUS "OPTIONS: (to change it: -D<option>=<ON|OFF>)")
message(STATUS "")
message(STATUS "Build testing applications (TEST_APP) ... ${TEST_APP}${TEST_APP_MESSAGE}")
message(STATUS "Generate API documentation (DOC) ... ${DOC}${DOC_MESSAGE}")
message(STATUS "")
