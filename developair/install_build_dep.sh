#!/bin/bash

# This needs bash. Don't run it in another shell. Especially sh. 

set -e
set -x

# 1 --- Check we're running as root.
if [ "$EUID" -ne 0 ]
  then echo "Please run as root"
  exit 126
fi

# using debian main ensures quite some stability 
echo 'deb [trusted=true] http://www.lrde.epita.fr/repo/debian/ unstable/' >> /etc/apt/sources.list && \
    apt-get update && \
    RUNLEVEL=1 DEBIAN_FRONTEND=noninteractive \
    apt-get install -y --no-install-recommends \
    wget git build-essential debhelper \
    emacs-nox emacs-goodies-el org-mode \
    make gcc g++ \
    swig4.0 \
    autoconf automake libtool libltdl-dev \
    flex bison \
    graphviz imagemagick \
    doxygen \
    help2man pandoc groff \
    python-all-dev python3-all-dev python3-pandas python3-ipykernel \
    python3-nbconvert python3-entrypoints python3-pygments ipython3 \
    python3-pip pypy3 pypy3-dev jupyter jupyter-nbconvert \
    r-base-core r-cran-data.table r-cran-ggplot2 \
    latexmk texlive-latex-extra texlive-fonts-extra \
    fonts-roboto \
    texlive-science \
    devscripts git-buildpackage cmake dh-python \
    libbdd0c2 libbdd-dev zlib1g-dev \
    locales \
    divine-ltsmin spins spin \
    default-jdk ant dot2tex pdf2svg lcov npm \
    g++-mingw-w64-i686 patch \
    dh-python 

apt-get clean
rm -rf /var/lib/apt/lists/* && \
sed -i 's/# \+\(en_US.UTF.*\)/\1/' /etc/locale.gen
locale-gen
ipython3 -c 'exit;'


### nice part ends here, time to compile

# LTL2BA
V=1.3
wget https://www.lrde.epita.fr/dload/spot/deps/ltl2ba-$V.tar.gz
tar xvf ltl2ba-$V.tar.gz
cd ltl2ba-$V
make -j4
mv ltl2ba /usr/local/bin/
cd ..
rm -rf ltl2ba-$V ltl2ba-$V.tar.gz

# LTL3BA
V=1.1.3
wget https://www.lrde.epita.fr/dload/spot/deps/ltl3ba-$V.tar.gz
tar xvf ltl3ba-$V.tar.gz
cd ltl3ba-$V
make -j4
mv ltl3ba /usr/local/bin/
cd ..
rm -rf ltl3ba-$V ltl3ba-$V.tar.gz

# LTL3DRA
V=0.3.0
wget https://github.com/xblahoud/ltl3dra/archive/v$V.tar.gz -O ltl3dra-$V.tar.gz
tar xvf ltl3dra-$V.tar.gz
cd ltl3dra-$V
make -j4
mv ltl3dra /usr/local/bin/
cd ..
rm -rf ltl3dra-$V ltl3dra-$V.tar.gz

# ltl2dstar
V=0.5.4
wget https://www.lrde.epita.fr/dload/spot/deps/ltl2dstar-$V.tar.gz
tar xvf ltl2dstar-$V.tar.gz
cd ltl2dstar-$V/src
make -j4
mv ltl2dstar /usr/local/bin/
cd ../..
rm -rf ltl2dstar-$V ltl2dstar-$V.tar.gz

# glugose 4.0
wget https://www.lrde.epita.fr/dload/spot/deps/glucose-syrup.tgz
tar xvf glucose-syrup.tgz
cd glucose-syrup/simp
make -j4
mv glucose /usr/local/bin
cd ../..
rm -rf glucose-syrup glucose-syrup.tgz

# modella 1.5.9
wget https://www.lrde.epita.fr/dload/spot/deps/MoDeLLa-1.5.9.tar.gz
tar xvf MoDeLLa-1.5.9.tar.gz
cd MoDeLLa-1.5.9
perl -pi -e 's/CFLAGS = .*$/$& -fcommon/' Makefile
make -j4
mv modella /usr/local/bin
cd ..
rm -rf MoDeLLa-1.5.9 MoDeLLa-1.5.9.tar.gz

# lbt 1.2.2
wget https://www.lrde.epita.fr/dload/spot/deps/lbt-1.2.2.tar.gz
tar xvf lbt-1.2.2.tar.gz
cd lbt-1.2.2
make -j4
cp lbt /usr/local/bin
cd ..
rm -rf lbt-1.2.2 lbt-1.2.2.tar.gz

# lbtt 1.2.1a
wget http://www.lrde.epita.fr/dload/spot/lbtt-1.2.1a.tar.gz
tar xvf lbtt-1.2.1a.tar.gz
cd lbtt-1.2.1a
./configure
make -j4
make install
cd ..
rm -rf lbtt-1.2.1a lbtt-1.2.1a.tar.gz

# valgrind 3.17.0
# Needed to read DWARF5 from gcc 11
wget https://sourceware.org/pub/valgrind/valgrind-3.17.0.tar.bz2
tar xvf valgrind-3.17.0.tar.bz2
cd valgrind-3.17.0
./configure
make -j4
make install
cd ..
rm -rf valgrind-3.17.0 valgrind-3.17.0.tar.bz2

# GAL2C
wget -O gal2c 'https://gitlab.lrde.epita.fr/spot/spot-gal2c/-/jobs/artifacts/master/raw/libITS/bin/gal2c?job=gal2c'
chmod a+x gal2c
mv gal2c /usr/local/bin

# dot2tex
pip3 install dot2tex

# svgo
npm install -g svgo@1.3.2
