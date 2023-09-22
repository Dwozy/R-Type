cmake_minimum_required(VERSION 3.27.1)

set(PROJECT_NAME "GameEngine")
set(LIBRARY_NAME "GameEngine")

set(INCLUDES include)
set(SRCS
    src/Main.cpp
)

project(${PROJECT_NAME})

find_package(nlohmann_json CONFIG REQUIRED)
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/lib/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/lib/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/lib/)

file(MAKE_DIRECTORY ${PROJECT_NAME})

add_library(${LIBRARY_NAME} STATIC ${SRCS})
target_link_libraries(${LIBRARY_NAME} INTERFACE sfml-system sfml-network sfml-graphics sfml-window)
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDES})
file(COPY ${INCLUDES}/ DESTINATION ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/include)
