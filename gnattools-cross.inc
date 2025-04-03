require gcc-configure-common.inc

EXTRA_OECONF_PATHS = "\
    --with-sysroot=/not/exist \
    --with-build-sysroot=${STAGING_DIR_TARGET} \
"

do_configure () {
	echo "Nothing to configure"
}
EXTRACONFFUNCS += "extract_stashed_builddir"
do_configure[depends] += "${COMPILERDEP}"

do_compile () {
        #export AR_FOR_TARGET="${TARGET_SYS}-ar"
        #export RANLIB_FOR_TARGET="${TARGET_SYS}-ranlib"
        #export LD_FOR_TARGET="${TARGET_SYS}-ld"
        #export NM_FOR_TARGET="${TARGET_SYS}-nm"
        #export CC_FOR_TARGET="${CCACHE} ${TARGET_SYS}-gcc"
        #export CFLAGS_FOR_TARGET="${TARGET_CFLAGS}"
        #export CPPFLAGS_FOR_TARGET="${TARGET_CPPFLAGS}"
        #export CXXFLAGS_FOR_TARGET="${TARGET_CXXFLAGS}"
        #export LDFLAGS_FOR_TARGET="${TARGET_LDFLAGS}"
        #export CC="${CC_FOR_TARGET} ${CFLAGS_FOR_TARGET}"

	#cd ${B}/${TARGET_SYS}/libada/
	#oe_runmake MULTIBUILDTOP=${B}/${TARGET_SYS}/libada/
	cd ${B}/gcc
	oe_runmake cross-gnattools
}

do_install () {
        #export INSTALL='install'
        #export INSTALL_DATA='install -m 644'
        #export AR_FOR_TARGET="${TARGET_SYS}-ar"
        cd ${B}/gcc
        sed -i -e '/Installation directories/,/UNSORTED/s/= .*recipe-sysroot-native/= /' Makefile
        oe_runmake 'DESTDIR=${D}' gnat-install-tools
        chown -R root:root ${D}
        echo '${bindir}/${TARGET_SYS}'="${bindir}/${TARGET_SYS}" TARGET_PREFIX="${TARGET_PREFIX}"
        #ls -1 ${bindir}/${TARGET_PREFIX}*
}

# avoid virtual/libc
INHIBIT_DEFAULT_DEPS = "1"
DEPENDS = "virtual/${HOST_PREFIX}gcc virtual/${HOST_PREFIX}compilerlibs"

BBCLASSEXTEND = "nativesdk"

PACKAGES = "\
    ${PN} \
    ${PN}-dbg \
"

LICENSE:${PN} = "GPL-3.0-with-GCC-exception"

FILES:${PN} = "\
    ${bindir}/${TARGET_SYS}/${TARGET_PREFIX}* \
"
#    ${prefix_native}/bin/${TARGET_PREFIX}* \
#    ${bindir}/${TARGET_PREFIX}* \
#    ${prefix}/bin/${TARGET_SYS}/* 

INSANE_SKIP:${MLPREFIX}${PN} = "buildpaths"
INSANE_SKIP:${MLPREFIX}${PN}-dbg = "buildpaths"

#do_package_write_ipk[depends] += "virtual/${MLPREFIX}libc:do_packagedata"
#do_package_write_deb[depends] += "virtual/${MLPREFIX}libc:do_packagedata"
#do_package_write_rpm[depends] += "virtual/${MLPREFIX}libc:do_packagedata"

#python __anonymous () {
#    f = d.getVar("ADA")
#    if "ada" not in f:
#        raise bb.parse.SkipRecipe("libada needs Ada support to be enabled in the compiler")
#}
