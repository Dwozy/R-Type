cmake_minimum_required(VERSION 3.20.1)
set(CMAKE_CXX_STANDARD 20)

set(PROJECT_NAME "R-Type")
set(LIBRARY_NAME "GameEngine")

#set(CMAKE_VERBOSE_MAKEFILE ON)

message(CHECK_START "Fetching dependencies...")
list(APPEND CMAKE_MESSAGE_INDENT "  ")

include(FetchContent)
message(CHECK_START "Fetching SFML...")
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)
message(CHECK_PASS "Done")

message(CHECK_START "Fetching nholmann-json...")
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)
message(CHECK_PASS "Done")

message(CHECK_START "Fetching asio...")
FetchContent_Declare(
  asiocmake
  GIT_REPOSITORY "https://github.com/OlivierLDff/asio.cmake"
  GIT_TAG        "main"
)
FetchContent_MakeAvailable(asiocmake)
message(CHECK_PASS "Done")

message(CHECK_START "Fetching googletest...")
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
message(CHECK_PASS "Done")

list(POP_BACK CMAKE_MESSAGE_INDENT)

project(${PROJECT_NAME} LANGUAGES CXX)

set(INCLUDES_GLOBAL include)

include("GameEngine/game_engine.cmake")
include("R-Type/client.cmake")
include("R-Type-server/server.cmake")
include("tests/tests.cmake")