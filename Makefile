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

ACTIONS_TEST=${BIN_DIR}/actions_test
COMMAND_TEST=${BIN_DIR}/command_test
KEY_EVENT_TEST=${BIN_DIR}/key_event_test
MOUSE_EVENT_TEST=${BIN_DIR}/mouse_event_test

export LD_LIBRARY_PATH=${LIB_DIR}

ifeq ($(test_app), on)
	BUILD_TEST_APP=--test-app
endif

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

${BUILD_DIR}/Makefile: premake4.lua src/premake4.lua test/premake4.lua
	@rm -rf ${BUILD_DIR}
	@mkdir -p ${BUILD_DIR}
	@cd ${BUILD_DIR} && ${PREMAKE} --file=${BASE_DIR}/premake4.lua ${BUILD_TEST_APP} --to gmake

build: configure
	@cd ${BUILD_DIR} && ${MAKE} config=$(config) --no-print-directory

run-actions-test:
	-@${GDB} ${ACTION_TEST}

run-command-test:
	-@${GDB} ${COMMAND_TEST}

run-key-event-test:
	-@${GDB} ${KEY_EVENT_TEST}

run-mouse-event-test:
	-@${GDB} ${MOUSE_EVENT_TEST}

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
