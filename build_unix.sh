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

fclean_game_r-type()
{
    cd ./R-Type/
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

build_game_r-type()
{
    cd ./R-Type/
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
    build_game_r-type
}

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
touch r-type_server
touch r-type_client
