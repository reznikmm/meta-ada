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

do_configure[noexec] = "1"

do_compile () {
        ${TARGET_PREFIX}gnatmake  --RTS=${RECIPE_SYSROOT}/${libdir}/gcc/${TARGET_SYS}/14.2.0 hello.adb
}

do_install () {
	install -Dm0755 ${B}/hello ${D}/${bindir}/hello
	:
}

## FIXME proper fix should be here
INSANE_SKIP:${PN}-dbg = "buildpaths"

