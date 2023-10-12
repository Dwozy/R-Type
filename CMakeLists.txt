cmake_minimum_required(VERSION 3.20.1)
set(CMAKE_CXX_STANDARD 20)

set(PROJECT_NAME "R-Type")
set(LIBRARY_NAME "GameEngine")

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

set(INCLUDES_LIB GameEngine/include)
set(SRCS_LIB
    GameEngine/src/Error.cpp
    GameEngine/src/DeltaTime.cpp
    GameEngine/src/systems/ControlSystem.cpp
    GameEngine/src/systems/DrawSystem.cpp
    GameEngine/src/systems/PositionSystem.cpp
    GameEngine/src/systems/CollisionSystem.cpp
    GameEngine/src/systems/PressableSystem.cpp
)

project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/GameEngine/${LIBRARY_NAME}/lib/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/GameEngine/${LIBRARY_NAME}/lib/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/GameEngine/${LIBRARY_NAME}/lib/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/GameEngine/${LIBRARY_NAME}/lib/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/GameEngine/${LIBRARY_NAME}/lib/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/GameEngine/${LIBRARY_NAME}/lib/)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/GameEngine/${LIBRARY_NAME}/lib/)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/GameEngine/${LIBRARY_NAME}/lib/)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/GameEngine/${LIBRARY_NAME}/lib/)

file(MAKE_DIRECTORY GameEngine/${LIBRARY_NAME})

add_library(${LIBRARY_NAME} STATIC ${SRCS_LIB})
target_include_directories(${LIBRARY_NAME} PRIVATE ${INCLUDES_LIB})
target_link_libraries(${LIBRARY_NAME} PRIVATE sfml-graphics sfml-audio sfml-system sfml-window)
target_link_libraries(${LIBRARY_NAME} PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(${LIBRARY_NAME} PRIVATE asio::asio)

set(CLIENT_BINARY_NAME "r-type_client")

set(INCLUDES_CLIENT R-Type/include)
set(SRCS_CLIENT
    R-Type/src/main.cpp
)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${PROJECT_NAME})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/${PROJECT_NAME})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/${PROJECT_NAME})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${PROJECT_NAME})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/${PROJECT_NAME})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/${PROJECT_NAME})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${PROJECT_NAME})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/${PROJECT_NAME})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/${PROJECT_NAME})

add_executable(${CLIENT_BINARY_NAME} ${SRCS_CLIENT})
if (UNIX)
    target_link_libraries(${CLIENT_BINARY_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/GameEngine/GameEngine/lib/libGameEngine.a)
endif (UNIX)
if (MSVC)
    target_link_libraries(${CLIENT_BINARY_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/GameEngine/GameEngine/lib/GameEngine.lib)
endif (MSVC)
target_link_libraries(${CLIENT_BINARY_NAME} PRIVATE sfml-graphics sfml-audio sfml-system sfml-window)
target_link_libraries(${CLIENT_BINARY_NAME} PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(${CLIENT_BINARY_NAME} PRIVATE asio::asio)
target_include_directories(${CLIENT_BINARY_NAME} PRIVATE ${INCLUDES_CLIENT} ${CMAKE_SOURCE_DIR}/GameEngine/include/)
