set(LIBRARY_NAME libGameEngine)
set(PROJECT_NAME GameEngine)

project(${PROJECT_NAME})

set(SRCS
    src/Error.cpp
)

set(INCLUDES include)

add_library(${PROJECT_NAME} STATIC ${SRCS})

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDES})

file(COPY ${INCLUDES}/ DESTINATION ${CMAKE_SOURCE_DIR}/${PROJECT_NAME})

add_executable(test main.cpp)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(CMAKE_CXX_COMPILER cl)
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(CMAKE_CXX_COMPILER g++)
endif()

target_link_libraries(test ${CMAKE_SOURCE_DIR}/${LIBRARY_NAME}.a)
