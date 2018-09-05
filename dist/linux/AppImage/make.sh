#!/bin/bash

cd ../../../

buildSuccess=0

cmake --build cmake-build-release --target huli -- -j 2 || buildSuccess=1

if [ ! ${buildSuccess} = 0 ]; then
    echo "Build Failed"
    exit 1
fi;

cd dist/linux/AppImage

if [ ! -d tools ]; then
    mkdir tools
fi

if [ ! -f 'tools/linuxdeployqt-continuous-x86_64.AppImage' ]; then
    cd tools
    wget "https://github.com/probonopd/linuxdeployqt/releases/download/continuous/linuxdeployqt-continuous-x86_64.AppImage"
    cd ..
fi

chmod +x tools/linuxdeployqt-continuous-x86_64.AppImage

if [ -d AppDir ]; then
    rm -rf AppDir
fi;

cp -r dirSrc AppDir

if [ -f ../../../cmake-build-release/huli ]; then
    cd AppDir/usr/bin
    cp ../../../../../../cmake-build-release/huli huli
    cd ../../../
else
    echo "Executable not found in build directory"
    exit 1
fi;

export ARCH="x86_64"

ARCH=x86_64 ./tools/linuxdeployqt-continuous-x86_64.AppImage AppDir/usr/share/applications/huli.desktop -appimage