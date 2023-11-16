cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(xor LANGUAGES CXX)
find_package(neptune CONFIG REQUIRED)
message("neptune_DIR: ${neptune_DIR}")
message("neptune_INCLUDE_DIR: ${neptune_INCLUDE_DIR}")
include_directories(${neptune_INCLUDE_DIR})
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} neptune::neptune)
add_custom_target(run
    COMMAND xor
    DEPENDS xor
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)