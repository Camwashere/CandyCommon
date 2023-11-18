cmake_minimum_required(VERSION 3.12)

project(nfd)

set(NFD_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/include/nfd.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/nfd_common.c
)

if(WIN32)
    list(APPEND NFD_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/nfd_win.cpp)
elseif(APPLE)
    list(APPEND NFD_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/nfd_cocoa.m)
else()
    list(APPEND NFD_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/nfd_gtk.c)
endif()

add_library(nfd ${NFD_SOURCES})

target_include_directories(nfd
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/include
)

if(APPLE)
    find_library(APPKIT_LIBRARY AppKit)
    target_link_libraries(nfd "${APPKIT_LIBRARY}")
elseif(NOT WIN32)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
    target_include_directories(nfd PUBLIC ${GTK3_INCLUDE_DIRS})
    target_link_libraries(nfd ${GTK3_LIBRARIES})
endif()