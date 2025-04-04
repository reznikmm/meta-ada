EXTRA_OECONF:append = " --disable-libada"

do_compile:append() {
        oe_runmake -C "${B}/gcc" cross-gnattools
}