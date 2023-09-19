#!/bin/bash

build()
{
    cmake -S . -B build
    make -C ./build
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
