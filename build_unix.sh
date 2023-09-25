#!/bin/bash

fclean_game_engine()
{
    cd ./GameEngine/
    source ./build_unix.sh fclean
    status=$?
    if [ "$status" -ne 0 ]; then
        exit "$status"
    fi
    cd ..
}

build_game_engine()
{
    cd ./GameEngine/
    source ./build_unix.sh
    status=$?
    if [ "$status" -ne 0 ]; then
        exit "$status"
    fi
    cd ..
}

fclean_all()
{
    fclean_game_engine
}

build_all()
{
    build_game_engine
}

install()
{
    cd ./submodules/vcpkg
    source bootstrap-vcpkg.sh
    status=$?
    if [ "$status" -ne 0 ]; then
        exit "$status"
    fi
    cd ../../
}

if [ "$1" == "install" ]
    then
    install
    exit
fi

if [ "$1" == "fclean" ]
    then
    fclean_all
fi

if [ "$1" == "engine" ]
    then
    if [ "$2" == "fclean" ]
        then
        fclean_game_engine
        exit
    fi
    build_game_engine
    exit
fi

build_all
