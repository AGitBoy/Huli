cmake_minimum_required(VERSION 3.10)
project(Huli)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTORCC ON)

set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5WebEngineWidgets)
find_package(Qt5Network)

include_directories(${Qt5Widgets_INCLUDE_DIRS})
include_directories(${Qt5WebEngineWidgets_INCLUDE_DIRS})
include_directories(${Qt5Network_INCLUDE_DIRS})

include_directories(src/)
include_directories(src/Util)
include_directories(src/Widgets)
include_directories(src/App)
include_directories(src/Suggestions)
include_directories(src/Suggestions/Providers)
include_directories(src/Web)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

add_executable(
	Huli
	huli.qrc
	src/main.cpp
	src/App/Window.h
	src/App/Window.cpp
	src/Suggestions/suggestion.cpp
	src/Suggestions/suggestion.h
	src/Widgets/AddressBar.cpp
	src/Widgets/AddressBar.h
	src/Widgets/AddressBarInput.cpp
	src/Widgets/AddressBarInput.h
	src/Widgets/Tabs.cpp
	src/Widgets/Tabs.h
	src/Widgets/ViewContainer.cpp
	src/Widgets/ViewContainer.h
	src/Widgets/WebView.h
	src/Widgets/WebView.cpp
	src/Suggestions/PopupObject.cpp
	src/Suggestions/PopupObject.h
	src/Suggestions/AbstactSuggestionProvider.h
	src/Suggestions/Providers/GoogleProvider.cpp
	src/Suggestions/Providers/GoogleProvider.h
	src/Util/urlValidation.h
	src/Util/urlValidation.cpp
	src/Widgets/PopupWindow.cpp
	src/Widgets/PopupWindow.h
	src/Suggestions/Providers/DuckDuckGoProvider.cpp
	src/Suggestions/Providers/DuckDuckGoProvider.h
	src/App/CLIParser.cpp
	src/App/CLIParser.h
	src/Web/WebPage.cpp
	src/Web/WebPage.h
	src/Widgets/DownloadManager.cpp
	src/Widgets/DownloadManager.h
	src/Widgets/DownloadItem.cpp
	src/Widgets/DownloadItem.h
	src/Util/getFilenameFromPath.h
	src/Util/getFilenameFromPath.cpp
	src/Widgets/TabBar.cpp
	src/Widgets/TabBar.h
	src/Util/fontUtils.cpp src/Util/fontUtils.h src/App/Config.cpp src/App/Config.h src/App/SearchEngine.cpp src/App/SearchEngine.h src/Suggestions/SuggestionEnum.h)

target_link_libraries(Huli Qt5::Widgets)
target_link_libraries(Huli Qt5::WebEngineWidgets)
target_link_libraries(Huli Qt5::Network)