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
    include/components/AnimationComponent.hpp
    include/components/HitboxComponent.hpp
    include/components/MovementComponent.hpp
    include/GUI/Gui.hpp
    include/GUI/PauseMenu.hpp
    include/states/EditorState.hpp
    include/states/GameState.hpp
    include/states/MainMenuState.hpp
    include/states/SettingsState.hpp
    include/states/State.hpp
    include/states/StateData.hpp
    include/map/Tile.hpp
    include/map/TileMap.hpp
    include/Entity.hpp
    include/Game.hpp
    include/GraphicsSettings.hpp
    include/Player.hpp
    src/components/AnimationComponent.cpp
    src/components/HitboxComponent.cpp
    src/components/MovementComponent.cpp
    src/GUI/Gui.cpp
    src/GUI/PauseMenu.cpp
    src/states/EditorState.cpp
    src/states/GameState.cpp
    src/states/MainMenuState.cpp
    src/states/SettingsState.cpp
    src/states/State.cpp
    src/states/StateData.cpp
    src/map/Tile.cpp
    src/map/TileMap.cpp
    src/Entity.cpp
    src/Game.cpp
    src/GraphicsSettings.cpp
    src/Player.cpp
    src/main.cpp)

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)
