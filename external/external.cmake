message(STATUS "Getting submodules")

message(STATUS "Looking for SFML")
find_package(SFML 2.5 COMPONENTS graphics audio QUIET)

if (NOT SFML_FOUND)
    message(STATUS "SFML not found, building from sources")
    execute_process(COMMAND git submodule update --init --recursive -- external/SFML
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
                add_subdirectory(external/SFML)

                set(RLRPG_YAML_TARGET SFML::SFML)
else()
    set(RLRPG_SFML_TARGET ${SFML_LIBRARIES})
endif()

