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

* clone yocto
* Apply `yocto-ada.patch`, copy GCC 14.2 patch `0099-libada.patch`, `libada` and `gnattools`:

```shell
patch -p1 < patches/yocto-ada.patch
cp -v patches/0099-libada.patch poky/meta/recipes-devtools/gcc/gcc/
cp -v *.bb *.inc poky/meta/recipes-devtools/gcc/
```

* create new `build`
```shell
source oe-init-build-env 
```

* Append `HOSTTOOLS`:
```shell
echo 'HOSTTOOLS += "gnatmake gnatlink gnatbind gnatls"' >> conf/local.conf
```

* Build `gcc-cross`, `libada`, `gnattools-cross`:

```shell
bitbake gcc-cross-x86_64
bitbake libada
bitbake gnattools-cross
```

* Then???
