EXTRA_OECONF:append = " --disable-libada"
LANGUAGES:append = ",ada"


do_compile:prepend() {
        # To find config/*/t-linux64 in Makefile in libada
        export GCC_BUILD_DIR="${B}/gcc"
}

do_install:prepend() {
        # To find config/*/t-linux64 in Makefile in libada
        export GCC_BUILD_DIR="${B}/gcc"
}

do_compile:append() {
        oe_runmake -C "${B}/gcc" cross-gnattools
}

