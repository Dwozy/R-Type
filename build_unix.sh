#!/bin/bash

clean_all()
{
    echo "-- Cleaning build folder"
    rm -rf "./build"
    echo "-- Cleaning build folder - done"
}

build_all()
{
    cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
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

if [ "$1" == "clean" ]
    then
    clean_all
    exit 0
fi

if [ "$1" == "fclean" ]
    then
    clean_all
    rm -rf GameEngine/GameEngine
    rm R-Type/r-type_client
    rm server/r-type_server
    exit 0
fi

build_all
#TMP
mkdir -p server
touch server/r-type_server
