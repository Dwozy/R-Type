set(SERVER_BINARY_NAME "r-type_server")

set(SERVER_FOLDER R-Type-server)

set(INCLUDES_SERVER ${SERVER_FOLDER}/include)
set(SRCS_SERVER
    ${SERVER_FOLDER}/src/main.cpp
    ${SERVER_FOLDER}/src/ClientSession.cpp
    ${SERVER_FOLDER}/src/RTypeServer.cpp
    ${SERVER_FOLDER}/src/TcpServer.cpp
    ${SERVER_FOLDER}/src/UdpServer.cpp
    ${SERVER_FOLDER}/src/Callback.cpp
    ${SERVER_FOLDER}/src/Event/HandlingConnection.cpp
    ${SERVER_FOLDER}/src/Event/HandlingCollision.cpp
    ${SERVER_FOLDER}/src/Event/HandlingTexture.cpp
    ${SERVER_FOLDER}/src/Event/HandlingTransform.cpp
    ${SERVER_FOLDER}/src/Event/HandlingDestroy.cpp
    ${SERVER_FOLDER}/src/Event/HandlingMove.cpp
    ${SERVER_FOLDER}/src/Event/HandlingShoot.cpp
    ${SERVER_FOLDER}/src/Event/HandlingInput.cpp
    ${SERVER_FOLDER}/src/Game/SetupGame.cpp
    ${SERVER_FOLDER}/src/Game/SpawnMob.cpp
    ${SERVER_FOLDER}/src/Game/UpdateGame.cpp
    ${SERVER_FOLDER}/src/HandlingEvent.cpp
    ${SERVER_FOLDER}/src/SetGameEngine.cpp
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
