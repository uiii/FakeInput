ifndef config
    config=debug
endif

# VARIABLES
export BASE_DIR=$(shell dirname $(shell readlink -f $(lastword $(MAKEFILE_LIST))))

export CONFIG_DIR=${BASE_DIR}/config
export BUILD_DIR=${BASE_DIR}/build
export BIN_DIR=${BASE_DIR}/bin
export INCLUDE_DIR=${BASE_DIR}/include
export LIB_DIR=${BASE_DIR}/lib
export TOOLS_DIR=${BASE_DIR}/tools

PREMAKE:=${TOOLS_DIR}/premake4-$(shell uname -m)

#UNIT_TESTS=${BIN_DIR}/unit_tests
#MANUAL_TESTS=${BIN_DIR}/manual_tests

export LD_LIBRARY_PATH=${LIB_DIR}

ifeq ($(config),debug)
    GDB=gdb -ex 'r'
endif

ifndef install_prefix
    INSTALL_PREFIX=/usr/local
else
    INSTALL_PREFIX=$(shell readlink -f $(install_prefix))
endif
export INSTALL_PREFIX

# TARGETS

.PHONY: all configure build clean unit-tests

all: configure build

configure: ${BUILD_DIR}/Makefile

${BUILD_DIR}/Makefile: premake4.lua src/premake4.lua #test/premake4.lua
	@rm -rf ${BUILD_DIR}
	@mkdir -p ${BUILD_DIR}
	@cd ${BUILD_DIR} && ${PREMAKE} --file=${BASE_DIR}/premake4.lua --to gmake

build: configure
	@cd ${BUILD_DIR} && ${MAKE} config=$(config) --no-print-directory

#run-unit-tests:
#	-@${UNIT_TESTS}

#run-manual-tests:
#	-@${GDB} ${MANUAL_TESTS}

dev-install:
	@${MAKE} -f ${CONFIG_DIR}/install/install.mk pkg-config INSTALL_PREFIX=${BASE_DIR} --no-print-directory

install:
	@${MAKE} -f ${CONFIG_DIR}/install/install.mk --no-print-directory

uninstall:
	@${MAKE} -f ${CONFIG_DIR}/install/uninstall.mk --no-print-directory

clean:
	@echo "Cleaning..."
	@if [ -d ${BUILD_DIR} ]; \
		then cd ${BUILD_DIR} && ${MAKE} clean --no-print-directory; \
	fi
	@rm -rf bin
	@rm -rf lib
	@rm -rf build
	@echo "Done."
