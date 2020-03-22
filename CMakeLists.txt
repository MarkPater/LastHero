cmake_minimum_required(VERSION 3.5)

file(STRINGS "VERSION.md" VERSION_LASTHERO)
project(LastHero
    VERSION ${VERSION_LASTHERO}
    DESCRIPTION "Open-Source RPG written in C++"
    LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall -pedantic")
set(CMAKE_BUILD_TYPE "Debug")

message(STATUS "LastHero version: ${VERSION_LASTHERO}")

include(external/external.cmake)
include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(${PROJECT_NAME}
    include/states/state.hpp
    include/states/gameState.hpp
    include/states/mainMenuState.hpp
    include/entity.hpp
    include/game.hpp
    src/states/state.cpp
    src/states/gameState.cpp
    src/states/mainMenuState.cpp
    src/entity.cpp
    src/game.cpp
    src/main.cpp)

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)