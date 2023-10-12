#!/bin/bash

./build_unix.sh

mkdir -p ./artifacts/client
mkdir -p ./artifacts/server

cp -r R-Type/assets ./artifacts/client

cp R-Type/r-type_client ./artifacts/client
cp R-Type/r-type_server ./artifacts/server

zip artifacts/r-type_client_linux_x86-64.zip ./artifacts/client/*
zip artifacts/r-type_server_linux_x86-64.zip ./artifacts/server/*
