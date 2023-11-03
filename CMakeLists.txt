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
set(gtest_force_exeared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
message(CHECK_PASS "Done")

if(DEBUG)
    message(CHECK_START "Fetching imgui...")
    FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG        "master"
    )
    FetchContent_MakeAvailable(imgui)
    set(IMGUI_DIR ${imgui_SOURCE_DIR})
    message(CHECK_PASS "Done")
    message(CHECK_START "Fetching imgui-sfml...")
    set(IMGUI_SFML_FIND_SFML OFF)
    FetchContent_Declare(
        imgui-sfml
        GIT_REPOSITORY https://github.com/SFML/imgui-sfml.git
        GIT_TAG        2.6.x
    )
    FetchContent_MakeAvailable(imgui-sfml)
    message(CHECK_PASS "Done")
endif()

list(POP_BACK CMAKE_MESSAGE_INDENT)

project(${PROJECT_NAME} LANGUAGES CXX)

set(INCLUDES_GLOBAL include)

if(DEBUG)
    add_compile_definitions(DEBUG)
    set(INCLUDES_DEBUG
        ${imgui_SOURCE_DIR}
        ${imgui-sfml_SOURCE_DIR}
        GameEngine/include/imgui/
    )
    set(SRCS_DEBUG GameEngine/src/Debug.cpp)
endif()

include("GameEngine/game_engine.cmake")
if(((NOT DEFINED BUILD_GAME_ENGINE) AND (NOT DEFINED BUILD_CLIENT) AND (NOT DEFINED BUILD_SERVER) AND (NOT DEFINED BUILD_TESTS) AND (NOT DEFINED BUILD_GAME_PLATFORMER)) OR (DEFINED BUILD_CLIENT))
  include("R-Type/client.cmake")
endif(((NOT DEFINED BUILD_GAME_ENGINE) AND (NOT DEFINED BUILD_CLIENT) AND (NOT DEFINED BUILD_SERVER) AND (NOT DEFINED BUILD_TESTS) AND (NOT DEFINED BUILD_GAME_PLATFORMER)) OR (DEFINED BUILD_CLIENT))
if(((NOT DEFINED BUILD_GAME_ENGINE) AND (NOT DEFINED BUILD_CLIENT) AND (NOT DEFINED BUILD_SERVER) AND (NOT DEFINED BUILD_TESTS) AND (NOT DEFINED BUILD_GAME_PLATFORMER)) OR (DEFINED BUILD_SERVER))
  include("R-Type-server/server.cmake")
endif(((NOT DEFINED BUILD_GAME_ENGINE) AND (NOT DEFINED BUILD_CLIENT) AND (NOT DEFINED BUILD_SERVER) AND (NOT DEFINED BUILD_TESTS) AND (NOT DEFINED BUILD_GAME_PLATFORMER)) OR (DEFINED BUILD_SERVER))
if(((NOT DEFINED BUILD_GAME_ENGINE) AND (NOT DEFINED BUILD_CLIENT) AND (NOT DEFINED BUILD_SERVER) AND (NOT DEFINED BUILD_TESTS) AND (NOT DEFINED BUILD_GAME_PLATFORMER)) OR (DEFINED BUILD_TESTS))
  include("tests/tests.cmake")
endif(((NOT DEFINED BUILD_GAME_ENGINE) AND (NOT DEFINED BUILD_CLIENT) AND (NOT DEFINED BUILD_SERVER) AND (NOT DEFINED BUILD_TESTS) AND (NOT DEFINED BUILD_GAME_PLATFORMER)) OR (DEFINED BUILD_TESTS))
if(((NOT DEFINED BUILD_GAME_ENGINE) AND (NOT DEFINED BUILD_CLIENT) AND (NOT DEFINED BUILD_SERVER) AND (NOT DEFINED BUILD_TESTS) AND (NOT DEFINED BUILD_GAME_PLATFORMER)) OR (DEFINED BUILD_GAME_PLATFORMER))
  include("Platformer/platformer.cmake")
endif(((NOT DEFINED BUILD_GAME_ENGINE) AND (NOT DEFINED BUILD_CLIENT) AND (NOT DEFINED BUILD_SERVER) AND (NOT DEFINED BUILD_TESTS) AND (NOT DEFINED BUILD_GAME_PLATFORMER)) OR (DEFINED BUILD_GAME_PLATFORMER))

if (DEFINED INSTALL)
  include(CPack)
endif (DEFINED INSTALL)