cmake_minimum_required(VERSION 3.20.1)
set(CMAKE_CXX_STANDARD 20)

set(PROJECT_NAME "R-Type")
set(BINARY_NAME "r-type_client")

set(INCLUDES include)
set(SRCS
    src/main.cpp
)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

FetchContent_Declare(
  asiocmake
  GIT_REPOSITORY "https://github.com/OlivierLDff/asio.cmake"
  GIT_TAG        "main"
)
FetchContent_MakeAvailable(asiocmake)


set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/)

project(${PROJECT_NAME} LANGUAGES CXX)
add_executable(${BINARY_NAME} ${SRCS})
if (UNIX)
    target_link_libraries(${BINARY_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/../GameEngine/GameEngine/lib/libGameEngine.a)
endif (UNIX)
if (MSVC)
    target_link_libraries(${BINARY_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/../GameEngine/GameEngine/lib/GameEngine.lib)
endif (MSVC)
target_link_libraries(${BINARY_NAME} PRIVATE sfml-graphics sfml-audio sfml-system sfml-window)
target_link_libraries(${BINARY_NAME} PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(${BINARY_NAME} PRIVATE asio::asio)
target_include_directories(${BINARY_NAME} PRIVATE ${INCLUDES} ${CMAKE_SOURCE_DIR}/../GameEngine/GameEngine/include/)
