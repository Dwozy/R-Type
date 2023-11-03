set(INCLUDES_LIB GameEngine/include)
set(SRCS_LIB
    GameEngine/src/Error.cpp
    GameEngine/src/Inputs.cpp
    GameEngine/src/DeltaTime.cpp
    GameEngine/src/systems/ControlSystem.cpp
    GameEngine/src/systems/DrawSystem.cpp
    GameEngine/src/systems/PositionSystem.cpp
    GameEngine/src/Network/ACommunication.cpp
    GameEngine/src/systems/CollisionSystem.cpp
    GameEngine/src/systems/PressableSystem.cpp
    GameEngine/src/systems/AnimationSystem.cpp
    GameEngine/src/systems/GravitySystem.cpp
    GameEngine/src/systems/CameraSystem.cpp
    GameEngine/src/systems/InputSystem.cpp
    GameEngine/src/SceneManager.cpp
    GameEngine/src/PrefabManager.cpp
)

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

if(DEBUG)
    add_library(${LIBRARY_NAME} STATIC ${SRCS_LIB} ${SRCS_DEBUG})
    target_include_directories(${LIBRARY_NAME} PRIVATE ${INCLUDES_DEBUG})
    target_link_libraries(${LIBRARY_NAME} PRIVATE ImGui-SFML::ImGui-SFML)
else()
    add_library(${LIBRARY_NAME} STATIC ${SRCS_LIB})
endif()
target_include_directories(${LIBRARY_NAME} PRIVATE ${INCLUDES_LIB})
target_link_libraries(${LIBRARY_NAME} PRIVATE sfml-graphics sfml-audio sfml-system sfml-window)
target_link_libraries(${LIBRARY_NAME} PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(${LIBRARY_NAME} PRIVATE asio)

if (DEFINED INSTALL)
    set(CPACK_PACKAGE_NAME "R-Type-Game-Engine")
    install(TARGETS ${LIBRARY_NAME} RUNTIME DESTINATION lib)
    install(DIRECTORY GameEngine/include DESTINATION include/GameEngine)
endif (DEFINED INSTALL)