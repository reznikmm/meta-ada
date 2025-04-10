# Create docker image
# docker build --tag=yocto \
#  --build-arg=NB_USER=$USER --build-arg=NB_UID=$UID - < Dockerfile
#
# Go into an working directory, clone yocto and meta-ada:
#
# git clone -b warrior git://git.yoctoproject.org/poky
# git -C poky clone -b warrior https://github.com/reznikmm/meta-ada
#
# Then start build.sh script
#
# docker run -v $PWD:$PWD --user=$USER \
#  --entrypoint=poky/meta-ada/.github/workflows/build.sh \
#  --env GITHUB_WORKSPACE=$PWD --workdir=$PWD --rm yocto

FROM fedora:29
ARG NB_USER=max
ARG NB_UID=1000
ENV NB_USER=${NB_USER}
ENV NB_UID=${NB_UID}

RUN dnf --assumeyes update
RUN dnf --assumeyes install gcc-gnat libgnat-devel libstdc++-static && \
  ln -s libgnat_pic.a /usr/lib/gcc/x86_64-redhat-linux/8/adalib/libgnat.a && \
  dnf --assumeyes install gawk make wget tar bzip2 gzip python3 unzip perl patch \
  diffutils diffstat git cpp gcc gcc-c++ glibc-devel texinfo chrpath \
  ccache perl-Data-Dumper perl-Text-ParseWords perl-Thread-Queue perl-bignum socat \
  python3-pexpect findutils which file cpio python python3-pip xz python3-GitPython \
  python3-jinja2 SDL-devel xterm && \
  dnf --assumeyes install hostname rpcgen && \
  adduser --uid ${NB_UID} ${NB_USER}
