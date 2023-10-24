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

set(INCLUDES_GLOBAL include)

set(INCLUDES_LIB GameEngine/include)
set(SRCS_LIB
    GameEngine/src/Error.cpp
    GameEngine/src/DeltaTime.cpp
    GameEngine/src/systems/ControlSystem.cpp
    GameEngine/src/systems/DrawSystem.cpp
    GameEngine/src/systems/PositionSystem.cpp
    GameEngine/src/Network/ACommunication.cpp
    GameEngine/src/systems/CollisionSystem.cpp
    GameEngine/src/systems/PressableSystem.cpp
    GameEngine/src/systems/AnimeSystem.cpp
    GameEngine/src/SceneManager.cpp
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
target_link_libraries(${LIBRARY_NAME} PRIVATE asio)

set(CLIENT_BINARY_NAME "r-type_client")

set(CLIENT_FOLDER R-Type)

set(INCLUDES_CLIENT ${CLIENT_FOLDER}/include)
set(SRCS_CLIENT
    ${CLIENT_FOLDER}/src/main.cpp
    ${CLIENT_FOLDER}/src/RTypeClient.cpp
    ${CLIENT_FOLDER}/src/EntityManager.cpp
    ${CLIENT_FOLDER}/src/UdpClient.cpp
    ${CLIENT_FOLDER}/src/HandleEvent.cpp
    ${CLIENT_FOLDER}/src/SetGameEngine.cpp
    ${CLIENT_FOLDER}/src/Event/ConnexionEvent.cpp
    ${CLIENT_FOLDER}/src/Event/DeleteEntityEvent.cpp
    ${CLIENT_FOLDER}/src/Event/MoveEntityEvent.cpp
    ${CLIENT_FOLDER}/src/Event/UpdateEntityEvent.cpp
    ${CLIENT_FOLDER}/src/Event/ShootEvent.cpp
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
target_link_libraries(${CLIENT_BINARY_NAME} PRIVATE asio)
target_include_directories(${CLIENT_BINARY_NAME} PRIVATE ${INCLUDES_CLIENT} ${INCLUDES_GLOBAL} ${CMAKE_SOURCE_DIR}/GameEngine/include/)

set(SERVER_BINARY_NAME "r-type_server")

set(SERVER_FOLDER R-Type-server)

set(INCLUDES_SERVER ${SERVER_FOLDER}/include)
set(SRCS_SERVER
    ${SERVER_FOLDER}/src/EntityManager.cpp
    ${SERVER_FOLDER}/src/main.cpp
    ${SERVER_FOLDER}/src/ClientSession.cpp
    ${SERVER_FOLDER}/src/RTypeServer.cpp
    ${SERVER_FOLDER}/src/TcpServer.cpp
    ${SERVER_FOLDER}/src/UdpServer.cpp
)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${SERVER_FOLDER})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/${SERVER_FOLDER})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/${SERVER_FOLDER})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${SERVER_FOLDER})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/${SERVER_FOLDER})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/${SERVER_FOLDER})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${SERVER_FOLDER})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/${SERVER_FOLDER})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/${SERVER_FOLDER})

add_executable(${SERVER_BINARY_NAME} ${SRCS_SERVER})
if (UNIX)
    target_link_libraries(${SERVER_BINARY_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/GameEngine/GameEngine/lib/libGameEngine.a)
endif (UNIX)
if (MSVC)
    target_link_libraries(${SERVER_BINARY_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/GameEngine/GameEngine/lib/GameEngine.lib)
endif (MSVC)
target_link_libraries(${SERVER_BINARY_NAME} PRIVATE asio)
target_link_libraries(${SERVER_BINARY_NAME} PRIVATE sfml-graphics sfml-audio sfml-system sfml-window)
target_link_libraries(${SERVER_BINARY_NAME} PRIVATE nlohmann_json::nlohmann_json)
target_include_directories(${SERVER_BINARY_NAME} PRIVATE ${INCLUDES_SERVER} ${INCLUDES_GLOBAL} ${CMAKE_SOURCE_DIR}/GameEngine/include/)

enable_testing()

set(TESTS_BINARY_NAME "unit_tests")

set(GAME_ENGINE_TESTS_FOLDER GameEngine/tests)

# set(INCLUDES_SERVER ${SERVER_FOLDER}/include)
set(SRCS_TESTS
    ${GAME_ENGINE_TESTS_FOLDER}/TestVector.cpp
)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Tests)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/Tests)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/Tests)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Tests)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/Tests)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/Tests)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Tests)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/Tests)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/Tests)

add_executable(
  ${TESTS_BINARY_NAME}
  ${SRCS_TESTS}
)
if (UNIX)
    target_link_libraries(${TESTS_BINARY_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/GameEngine/GameEngine/lib/libGameEngine.a)
endif (UNIX)
if (MSVC)
    target_link_libraries(${TESTS_BINARY_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/GameEngine/GameEngine/lib/GameEngine.lib)
endif (MSVC)
target_link_libraries(${TESTS_BINARY_NAME} PRIVATE GTest::gtest_main)
target_include_directories(${TESTS_BINARY_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/GameEngine/include/)
