#pragma once

#include <cstddef>
#include <cstdint>

#include <string>
#include <map>


namespace vsa::sim {

struct SimulationConfig
{
    std::size_t m_seed = 123456789;

    std::size_t max_duration_days = 10;

    struct Population
    {
        std::int32_t initial_population = 2000;

        std::int32_t initial_min_age = 20;
        std::int32_t initial_max_age = 60;

        std::int32_t min_couple_age = 18;
        std::int32_t diference_couple_age = 15;

        std::int32_t initial_max_children = 4;

        float percentage_of_women = 50.f;
        float percentage_of_men = 50.f;

        float death_probability_day_increment = 0.0000003f;

        float couple_creation_probability_per_day = 0.01f;
        float couple_breaking_probability_per_day = 0.0001f;
        float child_creation_probability_per_day = 0.003f;
    };
    Population population;

    struct Resident
    {
        float initial_percentage = 0.05f;
        float become_probability = 0.05f;
    };
    std::map<std::string, Resident> residents;
};

}
