EXTRA_OECONF:append = " --disable-libada"
LANGUAGES:append =  ",ada"


do_compile:append() {
        oe_runmake -C "${B}/gcc" cross-gnattools
}
