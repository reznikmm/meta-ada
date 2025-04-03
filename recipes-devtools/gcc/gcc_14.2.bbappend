FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI:append = "file://0099-libada.patch"

LANGUAGES:append = ",ada"

EXTRA_OECONF:append = " --disable-libada"