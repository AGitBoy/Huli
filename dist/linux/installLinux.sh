#!/usr/bin/env bash

cd ../../

buildSuccess=0

cmake --build cmake-build-release --target huli -- -j 2 || buildSuccess=1

if [ ! ${buildSuccess} = 0 ]; then
    echo "Build Failed"
    echo "Ensure you have the proper dependencies installed"
    exit 1
fi

cd dist/linux

function checkAndMakeDir() {
    if [ ! -d "$1" ]; then
        echo "$1 doesn't exist..."
        sudo mkdir -p "$1" || exit 1
        echo "Made folder $1"
    fi
}

checkAndMakeDir "/usr/local/bin"
checkAndMakeDir "/usr/share/applications"
checkAndMakeDir "/usr/share/icons/hicolor/256x256/apps"

sudo cp huli.desktop /usr/share/applications
sudo cp ../../cmake-build-release/huli /usr/local/bin/
sudo cp ../../res/icons/app/logo.svg /usr/share/icons/hicolor/256x256/apps/huli.svg
