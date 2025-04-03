# meta-ada
Meta layer for Yocto which adds support for Ada. 

## How to try

* Run fedora-41 in docker
* install rpms need for yocto
* install gnat 14.2

```shell
dnf install gcc-gnat libgnat-devel
```

* install libstdc++-static: 

```shell
dnf install libstdc++-static
```

* create `libgnat.a` to have static executables:

```shell
ln -s libgnat_pic.a /usr/lib/gcc/x86_64-redhat-linux/14/adalib/libgnat.a
```

* clone yocto styhead
* create new `build`
```shell
source oe-init-build-env
```

* Append `meta-ada` layer
```shell
bitbake-layers add-layer ../meta-ada
```

* Build `gcc-cross`, `libada`, `gnattools-cross`:
```shell
bitbake gcc-cross-x86_64
bitbake libada
bitbake gnattools-cross
```

* Then test???
