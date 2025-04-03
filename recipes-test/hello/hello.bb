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

# No information for SRC_URI yet (only an external source tree was specified)
FILESEXTRAPATHS:prepend := "${THISDIR}:"
SRC_URI = "file://source/hello.adb"
S = "${WORKDIR}/source"

DEPENDS = "libada gnattools-cross"

# NOTE: no Makefile found, unable to determine what needs to be done

do_configure () {
	# Specify any needed configure commands here
	:
}

do_compile () {
	# Specify compilation commands here
	${TARGET_PREFIX}gnatls -v --RTS=/home/max/yocto/poky/build/tmp/work/core2-64-poky-linux/hello/1.0/recipe-sysroot-native/usr/lib/gcc/x86_64-poky-linux/14.2.0
	${TARGET_PREFIX}gnatmake -vh --RTS=/home/max/yocto/poky/build/tmp/work/core2-64-poky-linux/hello/1.0/recipe-sysroot-native/usr/lib/gcc/x86_64-poky-linux/14.2.0 -aI${S} hello.adb \
         -largs --sysroot=/home/max/yocto/poky/build/tmp/work/core2-64-poky-linux/hello/1.0/recipe-sysroot
}

do_install () {
	# Specify install commands here
	:
}

