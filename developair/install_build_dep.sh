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
    apt-get install -y \
    wget git \
    emacs-nox emacs-goodies-el org-mode \
    make gcc g++ \
    swig4.0 \
    autoconf automake libtool \
    flex bison \
    graphviz imagemagick optipng \
    doxygen \
    help2man pandoc groff \
    python-all-dev python3-all-dev python3-pandas python3-ipykernel \
    python3-nbconvert python3-entrypoints python3-pygments ipython3 \
    r-base-core r-recommended- r-base-dev- r-base-html- \
    latexmk texlive-latex-extra texlive-fonts-extra \
    fonts-roboto \
    texlive-science \
    texlive-latex-extra-doc- texlive-fonts-extra-doc- \
    texlive-latex-base-doc- texlive-latex-recommended-doc- \
    texlive-pictures-doc- texlive-pstricks-doc- \
    texlive-fonts-recommended-doc- \
    devscripts git-buildpackage cmake \
    libbdd0c2 libbdd-dev zlib1g-dev \
    locales \
    divine-ltsmin spins spin \
    default-jdk ant dot2tex pdf2svg lcov \
    g++-mingw-w64-i686 gcc-snapshot \
    dh-python

apt-get clean
sed -i 's/# \+\(en_US.UTF.*\)/\1/' /etc/locale.gen
locale-gen
ipython3 -c 'exit;'


### nice part ends here, time to compile

#!/bin/sh

set -e  # Abort on any error
set -x  # Show each instruction as is it run

# GNU Libtool
V=2.4.6
wget http://ftpmirror.gnu.org/libtool/libtool-$V.tar.gz
tar xvf libtool-$V.tar.gz
cd libtool-$V
# Debian has its own libltdl that we want to use when
# building the Debian packages.
./configure --disable-ltdl-install
make -j4
make install
cd ..
rm -rf libtool-$V

# LTL2BA
V=1.2b1
wget http://www.lsv.ens-cachan.fr/~gastin/ltl2ba/ltl2ba-$V.tar.gz
tar xvf ltl2ba-$V.tar.gz
cd ltl2ba-$V
make -j4
mv ltl2ba /usr/local/bin/
cd ..
rm -rf ltl2ba-$V ltl2ba-$V.tar.gz

# LTL3BA
V=1.1.3
wget http://sourceforge.net/projects/ltl3ba/files/ltl3ba/1.1/ltl3ba-$V.tar.gz
tar xvf ltl3ba-$V.tar.gz
cd ltl3ba-$V
make -j4
mv ltl3ba /usr/local/bin/
cd ..
rm -rf ltl3ba-$V ltl3ba-$V.tar.gz

# LTL3DRA
V=0.2.5
wget http://sourceforge.net/projects/ltl3dra/files/ltl3dra-$V.tar.gz
tar xvf ltl3dra-$V.tar.gz
cd ltl3dra-$V
make -j4
mv ltl3dra /usr/local/bin/
cd ..
rm -rf ltl3dra-$V ltl3dra-$V.tar.gz

# ltl2dstar
V=0.5.3
wget http://www.ltl2dstar.de/down/ltl2dstar-$V.tar.gz
tar xvf ltl2dstar-$V.tar.gz
cd ltl2dstar-$V/src
make -j4
mv ltl2dstar /usr/local/bin/
cd ../..
rm -rf ltl2dstar-$V ltl2dstar-$V.tar.gz

# glugose 4.0
wget http://www.labri.fr/perso/lsimon/downloads/softwares/glucose-syrup.tgz
tar xvf glucose-syrup.tgz
cd glucose-syrup/simp
make -j4
mv glucose /usr/local/bin
cd ../..
rm -rf glucose-syrup

# modella 1.5.9
wget http://web.archive.org/web/20080607170403/http://www.science.unitn.it/~stonetta/modella/MoDeLLa-1.5.9.tar.gz
tar xvf MoDeLLa-1.5.9.tar.gz
cd MoDeLLa-1.5.9
make -j4
mv modella /usr/local/bin
cd ..
rm -rf MoDeLLa-1.5.9

# lbt 1.2.2
wget http://www.tcs.hut.fi/Software/maria/src/lbt-1.2.2.tar.gz
tar xvf lbt-1.2.2.tar.gz
cd lbt-1.2.2
make -j4
cp lbt /usr/local/bin
cd ..
rm -rf lbt-1.2.2

# lbtt 1.2.1a
wget http://www.lrde.epita.fr/dload/spot/lbtt-1.2.1a.tar.gz
tar xvf lbtt-1.2.1a.tar.gz
cd lbtt-1.2.1a
./configure
make -j4
make install
cd ..
rm -rf lbtt-1.2.1a

# Spin 6.4.6
# wget http://spinroot.com/spin/Src/src646.tar.gz
# tar xvf src646.tar.gz
# cd Src6.4.6
# make -j4
# mv spin /usr/local/bin
# cd ..
# rm -rf Src6.4.6

# GAL2C
wget http://teamcity.lrde.epita.fr/repository/download/Spot_Gal2cStretch/.lastSuccessful/gal2c?guest=1 -O gal2c
chmod a+x gal2c
mv gal2c /usr/local/bin

# dot2tex from git, because the last release from 2014 has bugs
git clone https://github.com/kjellmf/dot2tex.git
cd dot2tex
python setup.py install
cd ..
rm -rf dot2tex