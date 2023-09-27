#!/bin/bash

build()
{
    export CONAN_BUILD_DIR=build/build/Release/generators
    $CONAN_PATH install . --output-folder=build --build=missing -c tools.system.package_manager:mode=install
    cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=$CONAN_BUILD_DIR/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_MAKE_PROGRAM=$CMAKE_MAKE_PROGRAM
    status=$?
    if [ "$status" -ne 0 ]; then
        exit "$status"
    fi
    cmake --build ./build --config Release --clean-first
    status=$?
    if [ "$status" -ne 0 ]; then
        exit "$status"
    fi
}

fclean()
{
    echo "-- Cleaning build folder"
    rm -rf "./build"
    echo "-- Cleaning build folder - done"
    echo "-- Cleaning GameEngine folder"
    rm -rf "./GameEngine"
    echo "-- Cleaning GameEngine folder - done"
}

if [ "$1" == "fclean" ]
    then
    fclean
    exit
fi

if [ "$1" == "re" ]
    then
    fclean
    build
    exit
fi

build
