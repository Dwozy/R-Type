set(GAME_BINARY_NAME "platformer")

set(GAME_FOLDER Platformer)

set(INCLUDES_GAME ${GAME_FOLDER}/include)
set(SRCS_GAME
    ${GAME_FOLDER}/src/main.cpp
    ${GAME_FOLDER}/src/Platformer.cpp
    ${GAME_FOLDER}/src/SetGameEngine.cpp
    ${GAME_FOLDER}/src/ChangeScene.cpp
    ${GAME_FOLDER}/src/WinLoseScene.cpp
    ${GAME_FOLDER}/src/GameScene.cpp
    ${GAME_FOLDER}/src/MainMenuScene.cpp
    ${GAME_FOLDER}/src/PauseScene.cpp
    ${GAME_FOLDER}/src/MapLoader.cpp
    ${GAME_FOLDER}/src/CollisionCallbacks.cpp
)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${GAME_FOLDER})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/${GAME_FOLDER})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/${GAME_FOLDER})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${GAME_FOLDER})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/${GAME_FOLDER})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/${GAME_FOLDER})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${GAME_FOLDER})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/${GAME_FOLDER})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/${GAME_FOLDER})

if(DEBUG)
add_executable(${GAME_BINARY_NAME} ${SRCS_GAME} ${SRCS_DEBUG})
    target_include_directories(${GAME_BINARY_NAME} PRIVATE ${INCLUDES_DEBUG})
    target_link_libraries(${GAME_BINARY_NAME} PRIVATE ImGui-SFML::ImGui-SFML)
else()
    add_executable(${GAME_BINARY_NAME} ${SRCS_GAME})
endif()
if (UNIX)
    target_link_libraries(${GAME_BINARY_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/GameEngine/GameEngine/lib/libGameEngine.a)
endif (UNIX)
if (MSVC)
    target_link_libraries(${GAME_BINARY_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/GameEngine/GameEngine/lib/GameEngine.lib)
endif (MSVC)
target_link_libraries(${GAME_BINARY_NAME} PRIVATE sfml-graphics sfml-audio sfml-system sfml-window)
target_link_libraries(${GAME_BINARY_NAME} PRIVATE nlohmann_json::nlohmann_json)
target_include_directories(${GAME_BINARY_NAME} PRIVATE ${INCLUDES_GAME} ${INCLUDES_GLOBAL} ${CMAKE_SOURCE_DIR}/GameEngine/include/)

if (DEFINED INSTALL)
    set(CPACK_PACKAGE_NAME "SCP-Adventures")
    install(TARGETS ${GAME_BINARY_NAME} RUNTIME DESTINATION bin)
    install(DIRECTORY ${GAME_FOLDER}/assets/ DESTINATION bin/assets)
    install(DIRECTORY ${GAME_FOLDER}/maps/ DESTINATION bin/maps)
    install(DIRECTORY ${GAME_FOLDER}/config/ DESTINATION bin/config)
endif (DEFINED INSTALL)
