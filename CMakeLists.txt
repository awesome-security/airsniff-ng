cmake_minimum_required(VERSION 3.8)
project(airsniff_ng)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        commands/airplay-ng.history
        conf/sample.cfg
        src/build/airsniff-ng
        src/build/cmake_install.cmake
        src/build/CMakeCache.txt
        src/build/Makefile
        src/CMakeLists.txt
        src/color.h
        src/help.cpp
        src/main.cpp
        fix_shared_lib.sh
        LICENSE
        Makefile
        README.md)

add_executable(airsniff_ng ${SOURCE_FILES})