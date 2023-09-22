#!/bin/bash

build()
{
    cmake -S . -B build
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
