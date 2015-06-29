#!/bin/bash
CURDIR=`pwd`

DEPENDENCIES=(
    'https://github.com/jwerle/fs.c/archive/0.1.2.tar.gz'
    'https://github.com/jeradesign/MinUnit/archive/master.tar.gz'
    'https://github.com/clibs/commander/archive/1.3.2.tar.gz'
)

LIBUV_PACKAGE='https://github.com/libuv/libuv/archive/v1.6.1.tar.gz'
APT_PACKAGES='liblua5.1-0-dev libfcgi-dev lua5.1'

echo "====================================================="
echo "==== INSTALL SYSTEM DEPENDENCIES (requires sudo) ===="
echo "====================================================="
echo ""

echo "RUNNING: sudo apt-get install ${APT_PACKAGES}"
echo ""
sudo apt-get install ${APT_PACKAGES}

echo ""
echo "====================================================="
echo "============== INSTALLING DEPENDENCIES =============="
echo "====================================================="
echo ""

if [ -d "$CURDIR/src/deps" ]; then
    rm -rf ${CURDIR}/src/deps
fi

mkdir ${CURDIR}/src/deps
cd ${CURDIR}/src/deps

for url in ${DEPENDENCIES[*]}; do
    echo "FETCHING: $url"

    wget ${url} > /dev/null 2>&1
    tar -xf *.tar.gz
    rm *.tar.gz
done;

echo ""
echo "====================================================="
echo "========== INSTALLING LIBUV (requires sudo) ========="
echo "====================================================="
echo ""

echo "FETCHING: $LIBUV_PACKAGE"

wget ${LIBUV_PACKAGE} > /dev/null 2>&1
tar -xf *.tar.gz
rm *.tar.gz

cd ${CURDIR}/src/deps/libuv-1.6.1

echo "BUILDING LIBUV"
echo ""

sh autogen.sh > /dev/null 2>&1
./configure > /dev/null 2>&1
make > /dev/null 2>&1
sudo make install > /dev/null 2>&1

echo "DONE"

