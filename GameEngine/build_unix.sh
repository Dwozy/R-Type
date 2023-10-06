#!/bin/bash

build()
{
    export CMAKE_MAKE_PROGRAM=$(which make)
    export CMAKE_CXX_COMPILER=$(which g++)
    export INCLUDES_DIR=$(pwd)/include
    conan build . --output-folder=. --build=missing
    status=$?
    if [ "$status" -ne 0 ]; then
        exit "$status"
    fi
    status=$?
    if [ "$status" -ne 0 ]; then
        exit "$status"
    fi
}

fclean()
{
    echo "-- Cleaning build folder"
    sudo rm -rf "./build"
    echo "-- Cleaning build folder - done"
    echo "-- Cleaning GameEngine folder"
    sudo rm -rf "./GameEngine"
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
