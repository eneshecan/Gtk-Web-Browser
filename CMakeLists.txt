cmake_minimum_required(VERSION 3.2)
project(GtkWebBrowser)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTKMM3 gtkmm-3.0 REQUIRED)
PKG_CHECK_MODULES(WEBKIT webkit2gtk-4.0 REQUIRED)
include_directories(${GTKMM3_INCLUDE_DIRS} ${WEBKIT_INCLUDE_DIRS})

add_executable(GtkWebBrowser ${GtkWebBrowser_SRC} src/main.cpp src/WebView.cpp src/WebView.h src/Browser.cpp src/Browser.h src/Page.cpp src/Page.h)
target_link_libraries(GtkWebBrowser ${GTKMM3_LIBRARIES} ${WEBKIT_LIBRARIES})
