EXTRA_OECONF .= " --disable-libada"
LANGUAGES .= ",ada"

do_compile_prepend() {
        # To find config/*/t-linux64 in Makefile in libada
        export GCC_BUILD_DIR="${B}/gcc"
}

do_install_prepend() {
        # To find config/*/t-linux64 in Makefile in libada
        export GCC_BUILD_DIR="${B}/gcc"
}

do_compile_append() {
        oe_runmake -C "${B}/gcc" cross-gnattools
}

