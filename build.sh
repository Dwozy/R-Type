#!/bin/bash

clean_all()
{
    echo "-- Cleaning build folder"
    rm -rf "./build"
    echo "-- Cleaning build folder - done"
}

setup_all()
{
    cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
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
    rm -f R-Type/r-type_client
    rm -f R-Type-server/r-type_server
    rm -f unit_tests
    exit 0
fi

setup_game_engine()
{
    cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DBUILD_GAME_ENGINE=""
    status=$?
    if [ "$status" -ne 0 ]; then
        exit "$status"
    fi
}

setup_client()
{
    cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DBUILD_CLIENT=""
    status=$?
    if [ "$status" -ne 0 ]; then
        exit "$status"
    fi
}

setup_server()
{
    cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DBUILD_SERVER=""
    status=$?
    if [ "$status" -ne 0 ]; then
        exit "$status"
    fi
}

setup_tests()
{
    cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=""
    status=$?
    if [ "$status" -ne 0 ]; then
        exit "$status"
    fi
}

build()
{
    cmake --build ./build --config Release
    status=$?
    if [ "$status" -ne 0 ]; then
        exit "$status"
    fi
}

if [ "$1" == "GameEngine" ]; then
    setup_game_engine
    build
    exit 0
fi

if [ "$1" == "Client" ]; then
    setup_client
    build
    exit 0
fi

if [ "$1" == "Server" ]; then
    setup_server
    build
    exit 0
fi

if [ "$1" == "tests" ]; then
    setup_tests
    build
    exit 0
fi

setup_all
build