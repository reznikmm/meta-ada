# meta-ada
Meta layer for Yocto (`warrior` branch) which adds support for Ada. 

## How to try

To build the Ada crosscompiler, you need a native GNAT of the same (or the previous) version. There is no 8.x compiler in in Alire. You can install it from packages. If you install it in Fedora 29 run:

```shell
dnf install gcc-gnat libgnat-devel libstdc++-static
```

* create `libgnat.a` to have static executables:

  ```shell
  ln -s libgnat_pic.a /usr/lib/gcc/x86_64-redhat-linux/14/adalib/libgnat.a
  ```

* install rpms need for yocto (including `hostname` and `rpcgen`)

* clone yocto warrior
  ```shell
  git clone -b warrior git://git.yoctoproject.org/poky
  ```

* create new `build`
  ```shell
  source oe-init-build-env
  ```

* Append `meta-ada` layer
  ```shell
  git -C .. clone -b warrior https://github.com/reznikmm/meta-ada
  bitbake-layers add-layer ../meta-ada
  ```

* Build `gcc-cross`, `libada`:
  ```shell
  bitbake gcc-cross-x86_64
  bitbake libada
  ```

* Then test
  ```shell
  echo 'IMAGE_INSTALL_append = " hello"' >> conf/local.conf
  bitbake core-image-minimal
  runqemu qemux86-64
  # Login root
  hello
  # See Hello output
  ```

##  Known issue

* We don't enable Ada in target native gcc. We have Ada only in cross gcc for now.
