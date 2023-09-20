#!/bin/bash

build()
{
    cmake -S . -B build
    cmake --build ./build --config Release --clean-first
}

clean()
{
    echo "-- Cleaning build folder"
    rm -rf "./build"
    echo "-- Cleaning build folder - done"
}

if [ "$1" == "clean" ]
    then
    clean
    exit
fi

if [ "$1" == "rebuild" ]
    then
    clean
    build
    exit
fi

build
