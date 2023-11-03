set(CLIENT_BINARY_NAME "r-type_client")

set(CLIENT_FOLDER R-Type)

set(INCLUDES_CLIENT ${CLIENT_FOLDER}/include)
set(SRCS_CLIENT
    ${CLIENT_FOLDER}/src/main.cpp
    ${CLIENT_FOLDER}/src/RTypeClient.cpp
    ${CLIENT_FOLDER}/src/UdpClient.cpp
    ${CLIENT_FOLDER}/src/TcpClient.cpp
    ${CLIENT_FOLDER}/src/HandleEvent.cpp
    ${CLIENT_FOLDER}/src/SetGameEngine.cpp
    ${CLIENT_FOLDER}/src/Event/DeleteEntityEvent.cpp
    ${CLIENT_FOLDER}/src/Event/InputEvent.cpp
    ${CLIENT_FOLDER}/src/Event/StateTextureEvent.cpp
    ${CLIENT_FOLDER}/src/Event/TransformEvent.cpp
    ${CLIENT_FOLDER}/src/Event/TextureEvent.cpp
    ${CLIENT_FOLDER}/src/Event/CollisionEvent.cpp
    ${CLIENT_FOLDER}/src/Event/ControllableEvent.cpp
    ${CLIENT_FOLDER}/src/Callback.cpp
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

if(DEBUG)
    add_executable(${CLIENT_BINARY_NAME} ${SRCS_CLIENT} ${SRCS_DEBUG})
    target_include_directories(${CLIENT_BINARY_NAME} PRIVATE ${INCLUDES_DEBUG})
    target_link_libraries(${CLIENT_BINARY_NAME} PRIVATE ImGui-SFML::ImGui-SFML)
else()
    add_executable(${CLIENT_BINARY_NAME} ${SRCS_CLIENT})
endif()
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
