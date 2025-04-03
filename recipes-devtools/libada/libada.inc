require ${COREBASE}/meta/recipes-devtools/gcc/gcc-configure-common.inc

EXTRA_OECONF:append = " --disable-libada"

EXTRA_OECONF_PATHS = "\
    --with-sysroot=/not/exist \
    --with-build-sysroot=${STAGING_DIR_TARGET} \
"

do_configure () {
	rm -rf ${B}/${TARGET_SYS}/libada/
	mkdir -p ${B}/${TARGET_SYS}/libada/
	cd ${B}/${TARGET_SYS}/libada/
	chmod a+x ${S}/libada/configure
	relpath=${@os.path.relpath("${S}", "${B}/${TARGET_SYS}")}
	../$relpath/libada/configure ${CONFIGUREOPTS} ${EXTRA_OECONF}
	# Easiest way to stop bad RPATHs getting into the library since we have a
	# broken libtool here
	# sed -i -e 's/hardcode_into_libs=yes/hardcode_into_libs=no/' ${B}/${TARGET_SYS}/libada/libtool
}
EXTRACONFFUNCS += "extract_stashed_builddir"
do_configure[depends] += "${COMPILERDEP}"

do_compile () {
        export AR_FOR_TARGET="${TARGET_SYS}-ar"
        export RANLIB_FOR_TARGET="${TARGET_SYS}-ranlib"
        export LD_FOR_TARGET="${TARGET_SYS}-ld"
        export NM_FOR_TARGET="${TARGET_SYS}-nm"
        export CC_FOR_TARGET="${CCACHE} ${TARGET_SYS}-gcc"
        export CFLAGS_FOR_TARGET="${TARGET_CFLAGS}"
        export CPPFLAGS_FOR_TARGET="${TARGET_CPPFLAGS}"
        export CXXFLAGS_FOR_TARGET="${TARGET_CXXFLAGS}"
        export LDFLAGS_FOR_TARGET="${TARGET_LDFLAGS}"
        export CC="${CC_FOR_TARGET} ${CFLAGS_FOR_TARGET}"

	cd ${B}/${TARGET_SYS}/libada/
	oe_runmake MULTIBUILDTOP=${B}/${TARGET_SYS}/libada/
}

do_install () {
        export INSTALL='install'
        export INSTALL_DATA='install -m 644'
        export AR_FOR_TARGET="${TARGET_SYS}-ar"
	cd ${B}/${TARGET_SYS}/libada/
	oe_runmake 'DESTDIR=${D}' MULTIBUILDTOP=${B}/${TARGET_SYS}/libada/ install-libada
	chown -R root:root ${D}
}

# avoid virtual/libc
INHIBIT_DEFAULT_DEPS = "1"
DEPENDS = "virtual/${HOST_PREFIX}gcc virtual/${HOST_PREFIX}compilerlibs"

BBCLASSEXTEND = "nativesdk"

PACKAGES = "\
    ${PN}-dbg \
    ${PN} \
    ${PN}-dev \
    ${PN}-staticdev \
"

LICENSE:${PN} = "GPL-3.0-with-GCC-exception"
LICENSE:${PN}-dev = "GPL-3.0-with-GCC-exception"
LICENSE:${PN}-dbg = "GPL-3.0-with-GCC-exception"

FILES:${PN} = "${libdir}/gcc/${TARGET_SYS}/${BINV}/adalib/libgna*-*.so"
FILES:${PN}-dev = "\
    ${libdir}/gcc/${TARGET_SYS}/${BINV}/adainclude/* \
    ${libdir}/gcc/${TARGET_SYS}/${BINV}/adalib/*.ali \
    ${libdir}/gcc/${TARGET_SYS}/${BINV}/adalib/libgnat.so \
    ${libdir}/gcc/${TARGET_SYS}/${BINV}/adalib/libgnarl.so \
    ${libdir}/gcc/${TARGET_SYS}/${BINV}/ada_target_properties \
"
FILES:${PN}-staticdev = "${libdir}/gcc/${TARGET_SYS}/${BINV}/adalib/*.a"

INSANE_SKIP:${MLPREFIX}${PN} = "ldflags"
INSANE_SKIP:${MLPREFIX}${PN}-dbg = "buildpaths"

do_package_write_ipk[depends] += "virtual/${MLPREFIX}libc:do_packagedata"
do_package_write_deb[depends] += "virtual/${MLPREFIX}libc:do_packagedata"
do_package_write_rpm[depends] += "virtual/${MLPREFIX}libc:do_packagedata"

#python __anonymous () {
#    f = d.getVar("ADA")
#    if "ada" not in f:
#        raise bb.parse.SkipRecipe("libada needs Ada support to be enabled in the compiler")
#}
