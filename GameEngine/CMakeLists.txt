cmake_minimum_required(VERSION 3.16.3)

set(PROJECT_NAME "GameEngine")
set(LIBRARY_NAME "libGameEngine")

set(INCLUDES include)
set(SRCS
    src/Entity.cpp
    src/Error.cpp
    src/sfml/renderer.cpp
)

project(${PROJECT_NAME})

find_package(nlohmann_json CONFIG REQUIRED)
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY /home/sleo/Epitech3/R-Type/GameEngine)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG /home/sleo/Epitech3/R-Type/GameEngine)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE /home/sleo/Epitech3/R-Type/GameEngine)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY /home/sleo/Epitech3/R-Type/GameEngine)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG /home/sleo/Epitech3/R-Type/GameEngine)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE /home/sleo/Epitech3/R-Type/GameEngine)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY /home/sleo/Epitech3/R-Type/GameEngine)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG /home/sleo/Epitech3/R-Type/GameEngine)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE /home/sleo/Epitech3/R-Type/GameEngine)

# FOR STATIC LIBRARY
add_library(${PROJECT_NAME} STATIC ${SRCS})
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDES})
file(COPY ${INCLUDES}/ DESTINATION  /home/sleo/Epitech3/R-Type/GameEngine/${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} PRIVATE  /home/sleo/Epitech3/R-Type/GameEngine/libGameEngine sfml-system sfml-network sfml-graphics sfml-window)

project(test)

add_executable(test main.cpp)
target_include_directories(test PRIVATE  /home/sleo/Epitech3/R-Type/GameEngine/GameEngine)
target_link_libraries(test PRIVATE /home/sleo/Epitech3/R-Type/GameEngine/libGameEngine.a)
