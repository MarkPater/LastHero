message(STATUS "Getting submodules")

message(STATUS "Looking for SFML...")
find_package(SFML 2.5 COMPONENTS graphics window system QUIET)
if (NOT SFML_FOUND)
    message(STATUS "SFML not found, building from sources")
    
    execute_process(COMMAND git submodule update --init --recursive -- external/SFML
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    add_subdirectory(external/SFML)

    set(LastHero_SFML_TARGET SFML::SFML)
else()
    set(LastHero_SFML_TARGET ${SFML_LIBRARIES})
endif()