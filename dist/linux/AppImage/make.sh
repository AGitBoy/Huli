#!/usr/bin/env bash

prev_dir="$(pwd)"
script_dir="$(dirname $(realpath $0))"

cd "${script_dir}"

src_dir="$(realpath ../../../)"
img_dir="$(pwd)"

if [[ -d build ]]; then
    rm -rf build
fi

mkdir build && cd build
buildSuccess=0

cmake -DENABLE_X11_ICONS=OFF --target huli -- j 2 "$src_dir"

if [[ ! $? = 0 ]]; then
    echo "CMake Configuration Failed"
    exit 1
else
    makeSuccess=0
    make
    if [[ ! $? = 0 ]]; then
        echo "Make Failed"
        exit 1
    fi
fi

cd ../

if [[ ! -d tools ]]; then
    mkdir tools
fi

if [ ! -f 'tools/linuxdeployqt-continuous-x86_64.AppImage' ]; then
    cd tools
    wget "https://github.com/probonopd/linuxdeployqt/releases/download/continuous/linuxdeployqt-continuous-x86_64.AppImage"
    cd ..
fi

chmod +x tools/linuxdeployqt-continuous-x86_64.AppImage

if [[ -d AppDir ]]; then
    rm -rf AppDir
fi;

cp -r dirSrc AppDir

if [[ -f build/huli ]]; then
    cd ${img_dir}/AppDir/usr/bin
    cp ${img_dir}/build/huli huli
    cd ${img_dir}
else
    echo "Executable not found in build directory"
    exit 1
fi;

# Fix for https://github.com/probonopd/linuxdeployqt/issues/35
if python -mplatform | grep -qi Ubuntu; then
    mkdir ${img_dir}AppDir/lib
    cp /usr/lib/x86_64-linux-gnu/nss/* ${img_dir}/AppDir/lib
    excluded='-exclude-libs="libnss3.so,libnssutil3.so"'
fi

_arch = "x86_64"

if [[ "$(uname -s)" = "Linux" ]]; then
    _arch = "$(uname -p)"
fi

ARCH=${ARCH:-$_arch}
export ARCH

${img_dir}/tools/linuxdeployqt-continuous-x86_64.AppImage ${img_dir}/AppDir/usr/share/applications/huli.desktop -appimage "$excluded"

cd "${prev_dir}"
