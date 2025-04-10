#!/bin/bash

set -e
set -x
THIS=`realpath $0`
WORKDIR="${1:-${GITHUB_WORKSPACE}/poky/build}"
cd $(dirname ${WORKDIR})

DIR_UID=`stat --printf=%u .`

if [ $UID -ne $DIR_UID ]; then
   useradd -m -s /bin/bash -u $DIR_UID user
   su user "$THIS" "$@"
   exit
fi

pwd
ls -l
umask
umask 0002

  source oe-init-build-env
  bitbake-layers add-layer ../meta-ada
  [ -d ../meta-board ] || bitbake-layers create-layer ../meta-board
  bitbake-layers add-layer ../meta-board
  mkdir -p -v ../meta-board/conf/machine/
  export MACHINE=my-arm
  cp -v ../meta-ada/.github/workflows/$MACHINE.conf ../meta-board/conf/machine/
  bitbake gcc-cross-arm
  bitbake libada

ARTIFACTS=$PWD/../../artifacts
mkdir -p -v $ARTIFACTS

for J in tmp/deploy/rpm/cortexa9t2hf_neon/libada*.rpm ; do
   rpm2archive $J
   mv -v $J.tgz $ARTIFACTS
done

cd tmp/work/x86_64-linux/gcc-cross-arm/8.3.0-r0
tar caf $ARTIFACTS/gcc-cross-8.3.0-cortexa9t2hf_neon.tgz -C image/$PWD/recipe-sysroot-native .
