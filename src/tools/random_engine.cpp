#include "random_engine.hpp"

#include <tools/logger.hpp>

#include <tracy/Tracy.hpp>

namespace vsa::tools {

RandomEngine& RandomEngine::get_instance()
{
    {
        ZoneScopedN("Random Engine Instance");
        static RandomEngine instance;
        return instance;
    }
}

std::size_t RandomEngine::get_random_uint(std::size_t min, std::size_t max)
{
    {
        ZoneScopedN("Random Engine UInt");

        std::uniform_int_distribution d(min, max);

        return d(m_gen);
    }
}

std::int64_t RandomEngine::get_random_int(std::int64_t min, std::int64_t max)
{
    {
        ZoneScopedN("Random Engine Int");

        std::uniform_int_distribution d(min, max);

        return d(m_gen);
    }
}

bool RandomEngine::get_random_bool(float true_probability)
{
    {
        ZoneScopedN("Random Engine Bool");
        if (true_probability > 1) { VSA_LOG_INFO("tools", "Incorrect probability (> 0)."); }
        std::bernoulli_distribution d(true_probability);
        return d(m_gen);
    }
}

} // tools