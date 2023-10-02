#!/bin/bash

build()
{
    cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_MAKE_PROGRAM=$CMAKE_MAKE_PROGRAM
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
