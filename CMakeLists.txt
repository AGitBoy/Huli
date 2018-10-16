cmake_minimum_required(VERSION 3.10)
project(Huli)
set(CMAKE_CXX_STANDARD 11)

############## REQUIRED FOR QT5 TO WORK ################
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTORCC ON)

set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5WebEngineWidgets)
find_package(Qt5Network)

include_directories(${Qt5Widgets_INCLUDE_DIRS})
include_directories(${Qt5WebEngineWidgets_INCLUDE_DIRS})
include_directories(${Qt5Network_INCLUDE_DIRS})
########################################################

include_directories(src/)
include_directories(src/Util)
include_directories(src/Widgets)
include_directories(src/Widgets/AddressBar)
include_directories(src/Widgets/Tabs)
include_directories(src/App)
include_directories(src/Suggestions)
include_directories(src/Suggestions/Providers)
include_directories(src/Web)
include_directories(src/Web/Downloads)
include_directories(src/Web/Popups)
include_directories(src/Web/WebView)

########################## REQUIRED FOR QT5 TO WORK ############################
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
################################################################################

add_executable(
    huli
    huli.qrc
    src/main.cpp
    src/App/Window.h
    src/App/Window.cpp
    src/Suggestions/suggestion.h
    src/Widgets/AddressBar/AddressBar.cpp
    src/Widgets/AddressBar/AddressBar.h
    src/Widgets/AddressBar/AddressBarInput.cpp
    src/Widgets/AddressBar/AddressBarInput.h
    src/Widgets/Tabs/Tabs.cpp
    src/Widgets/Tabs/Tabs.h
    src/Widgets/Tabs/ViewContainer.cpp
    src/Widgets/Tabs/ViewContainer.h
    src/Web/WebView/WebView.h
    src/Web/WebView/WebView.cpp
    src/Suggestions/PopupObject.cpp
    src/Suggestions/PopupObject.h
    src/Suggestions/AbstactSuggestionProvider.h
    src/Suggestions/Providers/GoogleProvider.cpp
    src/Suggestions/Providers/GoogleProvider.h
    src/Web/Popups/PopupWindow.cpp
    src/Web/Popups/PopupWindow.h
    src/Suggestions/Providers/DuckDuckGoProvider.cpp
    src/Suggestions/Providers/DuckDuckGoProvider.h
    src/App/CLIParser.cpp
    src/App/CLIParser.h
    src/Web/WebView/WebPage.cpp
    src/Web/WebView/WebPage.h
    src/Web/Downloads/DownloadManager.cpp
    src/Web/Downloads/DownloadManager.h
    src/Web/Downloads/DownloadItem.cpp
    src/Web/Downloads/DownloadItem.h
    src/Widgets/Tabs/TabBar.cpp
    src/Widgets/Tabs/TabBar.h

    # TODO: Merge these into a util.h file
    src/Util/urlValidation.h
    src/Util/urlValidation.cpp
    src/Util/getFilenameFromPath.h
    src/Util/getFilenameFromPath.cpp
    src/Util/fontUtils.cpp
    src/Util/fontUtils.h

    src/App/Settings.cpp
    src/App/Settings.h
    src/Web/SearchEngine.cpp
    src/Web/SearchEngine.h
    src/Suggestions/SuggestionEnum.h
    src/Web/BrowserBase.cpp
    src/Web/BrowserBase.h
    src/Web/Popups/PopupWebView.cpp
    src/Web/Popups/PopupWebView.h
    src/Util/iconProvider.h
    src/Util/iconProvider.cpp
    src/Widgets/AddressBar/AddressBarLayoutLoader.cpp
    src/Widgets/AddressBar/AddressBarLayoutLoader.h
    src/globals.h)


########### REQUIRED FOR QT5 TO WORK ############
target_link_libraries(huli Qt5::Widgets)
target_link_libraries(huli Qt5::WebEngineWidgets)
target_link_libraries(huli Qt5::Network)
#################################################

include_directories(${CMAKE_CURRENT_BINARY_DIR})

option(ENABLE_X11_ICONS "Use X11 Icon Theme on X11" ON)

if(UNIX AND NOT APPLE)
    set(PLATFORM_X11 1)
else()
    set(PLATFORM_X11 0)
endif()

if(Qt5Widgets_VERSION VERSION_LESS 5.11.0)
    set(QT_11_SUPPORT 0)
else()
    set(QT_11_SUPPORT 1)
endif()

if(Qt5Widgets_VERSION VERSION_LESS 5.10.0)
    set(QT_10_SUPPORT 0)
else()
    set(QT_10_SUPPORT 1)
endif()

configure_file(config.h.in config.h)