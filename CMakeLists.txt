cmake_minimum_required(VERSION 3.5)

file(STRINGS "VERSION.md" VERSION_LASTHERO)
project(LastHero
    VERSION ${VERSION_LASTHERO}
    DESCRIPTION "Open-Source RPG written in C++"
    LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -pedantic")
set(CMAKE_BUILD_TYPE "Debug")

message(STATUS "LastHero version: ${VERSION_LASTHERO}")

include(external/external.cmake)
include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(${PROJECT_NAME}
    include/states/State.hpp
    include/states/GameState.hpp
    include/states/EditorState.hpp
    include/states/MainMenuState.hpp
    include/states/SettingsState.hpp
    include/components/HitboxComponent.hpp
    include/components/MovementComponent.hpp
    include/components/AnimationComponent.hpp
    include/GUI/PauseMenu.hpp
    include/GUI/Gui.hpp
    include/map/Tile.hpp
    include/map/TileMap.hpp
    include/Entity.hpp
    include/Player.hpp
    include/Game.hpp
    src/states/State.cpp
    src/states/GameState.cpp
    src/states/EditorState.cpp
    src/states/MainMenuState.cpp
    src/states/SettingsState.cpp
    src/components/HitboxComponent.cpp
    src/components/MovementComponent.cpp
    src/components/AnimationComponent.cpp
    src/GUI/PauseMenu.cpp
    src/GUI/Gui.cpp
    src/map/Tile.cpp
    src/map/TileMap.cpp
    src/Entity.cpp
    src/Player.cpp
    src/Game.cpp
    src/main.cpp)

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)
