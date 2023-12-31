#!/bin/bash

version="$1"

echo "-- Cleaning build folder"
rm -rf "./build"
echo "-- Cleaning build folder - done"

mkdir artifacts

cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DBUILD_CLIENT="" -DINSTALL=""
cd build && cpack --config CPackConfig.cmake -G ZIP && cpack --config CPackConfig.cmake -G STGZ
status=$?
if [ "$status" -ne 0 ]; then
    exit "$status"
fi
mv R-Type-client-0.1.1-Linux.zip ../artifacts/r-type_client-$version-linux_x86-64.zip
mv R-Type-client-0.1.1-Linux.sh ../artifacts/r-type_client-$version-linux_x86-64.sh
cd -
rm -rf build/CMakeCache.txt

cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DBUILD_SERVER="" -DINSTALL=""
cd build && cpack --config CPackConfig.cmake -G ZIP && cpack --config CPackConfig.cmake -G STGZ
status=$?
if [ "$status" -ne 0 ]; then
    exit "$status"
fi
mv R-Type-server-0.1.1-Linux.zip ../artifacts/r-type_server-$version-linux_x86-64.zip
mv R-Type-server-0.1.1-Linux.sh ../artifacts/r-type_server-$version-linux_x86-64.sh
cd -
rm -rf build/CMakeCache.txt

cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DBUILD_GAME_PLATFORMER="" -DINSTALL=""
cd build && cpack --config CPackConfig.cmake -G ZIP && cpack --config CPackConfig.cmake -G STGZ
status=$?
if [ "$status" -ne 0 ]; then
    exit "$status"
fi
mv SCP-Adventures-0.1.1-Linux.zip ../artifacts/scp_adventures-$version-linux_x86-64.zip
mv SCP-Adventures-0.1.1-Linux.sh ../artifacts/scp_adventures-$version-linux_x86-64.sh
cd -
rm -rf build/CMakeCache.txt

cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DBUILD_GAME_ENGINE="" -DINSTALL=""
cd build && cpack --config CPackConfig.cmake -G ZIP && cpack --config CPackConfig.cmake -G STGZ
status=$?
if [ "$status" -ne 0 ]; then
    exit "$status"
fi
mv R-Type-Game-Engine-0.1.1-Linux.zip ../artifacts/r-type_game_engine-$version-linux_x86-64.zip
mv R-Type-Game-Engine-0.1.1-Linux.sh ../artifacts/r-type_game_engine-$version-linux_x86-64.sh
cd -
rm -rf build/CMakeCache.txt
