#!/bin/bash
CURDIR=`pwd`

DEPENDENCIES=(
    'https://github.com/jwerle/fs.c/archive/0.1.2.tar.gz'
    'https://github.com/jeradesign/MinUnit/archive/master.tar.gz'
    'https://github.com/clibs/commander/archive/1.3.2.tar.gz'
)

LIBUV_PACKAGE='https://github.com/clibs/uv/archive/master.tar.gz'

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
    echo ""

    wget ${url}
    tar -xf *.tar.gz
    rm *.tar.gz
done;

echo "====================================================="
echo "========== INSTALLING LIBUV (requires sudo) ========="
echo "====================================================="
echo ""

wget $LIBUV_PACKAGE
tar -xf *.tar.gz
rm *.tar.gz

cd ${CURDIR}/src/deps/uv-master

sudo ./clib-install.sh

