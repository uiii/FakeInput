EXPAND_VARIABLES:=${TOOLS_DIR}/expand_variables.py

INCLUDE_FILES=$(shell find ${INCLUDE_DIR} -type f -print | sed -e "s;${BASE_DIR}/;;")
LIB_FILES=$(shell find ${LIB_DIR} -type f -executable -print | sed -e "s;${BASE_DIR}/;;")
PKGCONFIG_FILES=FakeInput.pc

.PHONY: install start_msg include lib pkg-config ${INCLUDE_FILES} ${LIB_FILES} ${PKGCONFIG_FILES}

install: start_msg include lib pkg-config

start_msg:
	@echo -e "install prefix: ${INSTALL_PREFIX}\n"

include: ${INCLUDE_FILES}

lib: ${LIB_FILES}

pkg-config: ${PKGCONFIG_FILES}

${INCLUDE_FILES}:
	@echo "install $@ ..."
	@install -m 0644 -D ${BASE_DIR}/$@ ${INSTALL_PREFIX}/$@

${LIB_FILES}:
	@echo "install $@ ..."
	@install -m 0755 -D ${BASE_DIR}/$@ ${INSTALL_PREFIX}/$@

${PKGCONFIG_FILES}:
	@echo "install lib/pkgconfig/$@ ..."
	@${EXPAND_VARIABLES} ${CONFIG_DIR}/pkgconfig/$@.in > /tmp/$@
	@install -m 0644 -D /tmp/$@ ${INSTALL_PREFIX}/lib/pkgconfig/$@
	@rm /tmp/$@
