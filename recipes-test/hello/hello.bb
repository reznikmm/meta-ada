# Recipe created by recipetool
# This is the basis of a recipe and may need further editing in order to be fully functional.
# (Feel free to remove these comments when editing.)

# Unable to find any files that looked like license statements. Check the accompanying
# documentation and source headers and set LICENSE and LIC_FILES_CHKSUM accordingly.
#
# NOTE: LICENSE is being set to "CLOSED" to allow you to at least start building - if
# this is not accurate with respect to the licensing of the software being built (it
# will not be in most cases) you must specify the correct value before using this
# recipe for anything other than initial testing/development!
LICENSE = "CLOSED"
LIC_FILES_CHKSUM = ""

SRC_URI = "file://hello.adb"

inherit gnatmake

S = "${WORKDIR}/sources"
UNPACKDIR = "${S}"

do_configure () {
	# Specify any needed configure commands here
	:
}

do_compile () {
	# Specify compilation commands here
	${TARGET_PREFIX}gnatls -v --RTS=${RECIPE_SYSROOT}/usr/lib/gcc/x86_64-poky-linux/14.2.0
	${TARGET_PREFIX}gnatmake -vh --RTS=${RECIPE_SYSROOT}/usr/lib/gcc/x86_64-poky-linux/14.2.0 -aI${S} hello.adb \
         -cargs ${TOOLCHAIN_OPTIONS} ${HOST_CC_ARCH} ${CFLAGS} \
         -largs ${TOOLCHAIN_OPTIONS} ${HOST_LD_ARCH} ${LDFLAGS}
}

do_install () {
	# Specify install commands here
	:
}

