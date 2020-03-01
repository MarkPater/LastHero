cmake_minimum_required(VERSION 3.5)

file(STRINGS "VERSION.md" VERSION_WBTG)
project(WBTG
        VERSION ${VERSION_WBTG}
        DESCRIPTION "Open-Source MMORPG written in C++"
        LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall -pedantic")
set(CMAKE_BUILD_TYPE "Debug")
set(SFML_DIR "${PROJECT_SOURCE_DIR}/External/SFML/lib/cmake/SFML") 

message(STATUS "WBTG version: ${VERSION_WBTG}")

find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)
include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(${PROJECT_NAME}
    src/main.cpp
)

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio sfml-system)
