EXPAND_VARIABLES:=${TOOLS_DIR}/expand_variables.py

INCLUDE_FILES=$(shell find ${INCLUDE_DIR} -type f -print | sed -e "s;${BASE_DIR}/;;")
LIB_FILES=$(shell find ${LIB_DIR} -type f -executable -print | sed -e "s;${BASE_DIR}/;;")
PKGCONFIG_FILES=lib/pkgconfig/FakeInput.pc

FILES=${LIB_FILES} ${INCLUDE_FILES} ${PKGCONFIG_FILES}

INCLUDE_DIRS=$(shell find ${INCLUDE_DIR}/* -type d -print | sed -e "s;${BASE_DIR}/;;" | tr ' ' '\n' | sort -r)
LIB_DIRS=$(shell find ${LIB_DIR}/* -type d -print | sed -e "s;${BASE_DIR}/;;" | tr ' ' '\n' | sort -r)

DIRS=${INCLUDE_DIRS} ${LIB_DIRS}

.PHONY: uninstall start_msg ${FILES} ${DIRS}

uninstall: start_msg ${FILES} ${DIRS}

start_msg:
	@echo -e "uninstall prefix: ${INSTALL_PREFIX}\n"

${FILES}:
	@if [ -f "${INSTALL_PREFIX}/$@" ]; then \
		echo "uninstall $@ ..."; \
		rm -f ${INSTALL_PREFIX}/$@; \
	fi

${DIRS}:
	@if [ -d ${INSTALL_PREFIX}/$@ ]; then \
   		if [ -z "`ls ${INSTALL_PREFIX}/$@`" ]; then \
			echo "uninstall $@ ..."; \
			rmdir ${INSTALL_PREFIX}/$@; \
		fi; \
	fi
