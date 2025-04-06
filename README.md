# meta-ada
Meta layer for Yocto which adds support for Ada. 

## How to try

To build the Ada crosscompiler, you need a native GNAT of the same (or previous) version. You can install it from Alire or from packages. If you install it in Fedora run:

```shell
dnf install gcc-gnat libgnat-devel libstdc++-static
```

* create `libgnat.a` to have static executables:

```shell
ln -s libgnat_pic.a /usr/lib/gcc/x86_64-redhat-linux/14/adalib/libgnat.a
```

* install rpms need for yocto

* clone yocto styhead
* create new `build`
```shell
source oe-init-build-env
```

* Append `meta-ada` layer
```shell
bitbake-layers add-layer ../meta-ada
```

* Build `gcc-cross`, `libada`:
```shell
bitbake gcc-cross-x86_64
bitbake libada
```

* Then test
```shell
echo 'IMAGE_INSTALL:append = " hello"' >> conf/local.conf
bitbake core-image-minimal
runqemu qemux86-64
# Login root
hello
# See Hello output
```

##  Known issue

* We rollback a patch from yocto `0010-Use-the-multilib-config-files-from-B-instead-of-usin.patch` without understanding the consequences.
* We don't enable Ada in target native gcc. We have Ada only in cross gcc for now.
