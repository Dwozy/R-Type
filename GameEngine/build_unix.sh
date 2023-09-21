#!/bin/bash

build()
{
    cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=/home/sleo/Epitech3/vcpkg/scripts/buildsystems/vcpkg.cmake
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
    echo "-- Cleaning libGameEngine.a"
    rm "./libGameEngine.a"
    echo "-- Cleaning libGameEngine.a - done"
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
