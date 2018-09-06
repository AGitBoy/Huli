# Huli
A QT5 based web browser, 
which aims to have feature completeness for all platforms.
This project is a WIP.

### Installing
##### Linux
###### From the source
The recommended method if there is no distribution package available is to build from the source.
Ensure you have the dependencies installed:
* Qt5 Development Packages
* Qt5 WebEngine
* CMake (Version 3.10 or greater is required)
* C++ Compiler

Then clone the repo, cd into it and run the following commands,
and type in your password when prompted:

`cd dist/linux && ./installLinux.sh`

###### AppImage
AppImages are available, but not recommended due to theme issues that
have not been resolved yet.
If you want to use the AppImage, download from our releases page, or
install the dependencies:
* Qt5 development packages
* Qt5 WebEngine
* AppImageLauncher
* CMake
* C++ Compiler

Clone this repo, cd into it, and run the following:

`cd dist/linux/AppImage && ./make.sh`

then the AppImage should be produced. Run the AppImage and it
should automatically install.


### Credits
Fallback action icons come from [this project](https://materialdesignicons.com/)