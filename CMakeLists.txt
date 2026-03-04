cmake_minimum_required(VERSION 3.27)
project(village)

set(CMAKE_CXX_STANDARD 23)

include(cmake/dependencies.cmake)
include(FetchContent)

FetchContent_Declare(
    tracy
    GIT_REPOSITORY https://github.com/wolfpld/tracy.git
    GIT_TAG master
)

FetchContent_MakeAvailable(tracy)

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/village_app.cpp
        src/village_app.hpp
        src/ui/renderer.cpp
        src/ui/renderer.hpp
        src/tools/logger.cpp
        src/tools/logger.hpp
        src/ui/window.cpp
        src/ui/window.hpp
        src/ui/test_window.cpp
        src/ui/test_window.hpp
        src/simulation/simulation_controller.cpp
        src/simulation/simulation_controller.hpp
        src/simulation/simulation.cpp
        src/simulation/simulation.hpp
        src/simulation/simulation_config.cpp
        src/simulation/simulation_config.hpp
        src/simulation/simulation_data.cpp
        src/simulation/simulation_data.hpp
        src/ui/main_window.cpp
        src/ui/main_window.hpp
        src/ui/configuration_window.cpp
        src/ui/configuration_window.hpp
        src/village/resident.hpp
        src/village/residents/resident_baker.cpp
        src/village/residents/resident_baker.hpp
        src/village/residents/resident_blacksmith.cpp
        src/village/residents/resident_blacksmith.hpp
        src/village/tool.hpp
        src/village/tools/tool_sickle.cpp
        src/village/tools/tool_sickle.hpp
        src/village/tools/tool_triphammer.cpp
        src/village/tools/tool_triphammer.hpp
        src/village/village.cpp
        src/village/village.hpp
        src/village/storage.cpp
        src/village/storage.hpp
        src/village/material.hpp
        src/village/materials/material_metal_ore.cpp
        src/village/materials/material_metal_ore.hpp
        src/village/materials/material_wheat.cpp
        src/village/materials/material_wheat.hpp
        src/village/residents/resident_miner.cpp
        src/village/residents/resident_miner.hpp
        src/village/dishes/dish_bread.cpp
        src/village/dishes/dish_bread.hpp
        src/village/dish.hpp
        src/village/village_builder.cpp
        src/village/village_builder.hpp
        src/village/village_factory.cpp
        src/village/village_factory.hpp
        src/village/entities_registry.cpp
        src/village/entities_registry.hpp
        src/village/entities_registrator.cpp
        src/village/residents/resident_factory.cpp
        src/village/residents/resident_factory.hpp
        src/tools/random_engine.cpp
        src/tools/random_engine.hpp
        src/village/resident.cpp
        src/village/village_config.cpp
        src/village/village_config.hpp
)

target_include_directories(${PROJECT_NAME} PRIVATE src/)

target_link_libraries(${PROJECT_NAME} PRIVATE imgui glm::glm json::json spdlog::spdlog Tracy::TracyClient)


