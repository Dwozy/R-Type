#!/bin/bash

rm -f build/CMakeCache.txt

debug=""
target="$1"
build_type="Release"
if [ "$1" == "-d" ]; then
    debug="-DDEBUG=On"
    build_type="RelWithDebInfo"
    target="$2"
fi

clean_all()
{
    echo "-- Cleaning build folder"
    rm -rf "./build"
    echo "-- Cleaning build folder - done"
}

setup_all()
{
    cmake -S . -B build -DCMAKE_BUILD_TYPE=$build_type $debug
    status=$?
    if [ "$status" -ne 0 ]; then
        exit "$status"
    fi
}

if [ "$target" == "clean" ]
    then
    clean_all
    exit 0
fi

if [ "$target" == "fclean" ]
    then
    clean_all
    rm -rf GameEngine/GameEngine
    rm -f R-Type/r-type_client
    rm -f R-Type-server/r-type_server
    rm -f Platformer/platformer
    rm -f unit_tests
    exit 0
fi

setup_game_engine()
{
    cmake -S . -B build -DCMAKE_BUILD_TYPE=$build_type -DBUILD_GAME_ENGINE="" $debug
    status=$?
    if [ "$status" -ne 0 ]; then
        exit "$status"
    fi
}

setup_client()
{
    cmake -S . -B build -DCMAKE_BUILD_TYPE=$build_type -DBUILD_CLIENT="" $debug
    status=$?
    if [ "$status" -ne 0 ]; then
        exit "$status"
    fi
}

setup_server()
{
    cmake -S . -B build -DCMAKE_BUILD_TYPE=$build_type -DBUILD_SERVER="" $debug
    status=$?
    if [ "$status" -ne 0 ]; then
        exit "$status"
    fi
}

setup_tests()
{
    cmake -S . -B build -DCMAKE_BUILD_TYPE=$build_type -DBUILD_TESTS="" $debug
    status=$?
    if [ "$status" -ne 0 ]; then
        exit "$status"
    fi
}

setup_game_platformer()
{
    cmake -S . -B build -DCMAKE_BUILD_TYPE=$build_type -DBUILD_GAME_PLATFORMER="" $debug
    status=$?
    if [ "$status" -ne 0 ]; then
        exit "$status"
    fi
}

build()
{
    cmake --build ./build --config $build_type
    status=$?
    if [ "$status" -ne 0 ]; then
        exit "$status"
    fi
}

if [ "$target" == "GameEngine" ]; then
    setup_game_engine
    build
    exit 0
fi

if [ "$target" == "Client" ]; then
    setup_client
    build
    exit 0
fi

if [ "$target" == "Server" ]; then
    setup_server
    build
    exit 0
fi

if [ "$target" == "tests" ]; then
    setup_tests
    build
    exit 0
fi

if [ "$target" == "Platformer" ]; then
    setup_game_platformer
    build
    exit 0
fi

setup_all
build
