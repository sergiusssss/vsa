//
// Created by Serhii Pustovit on 30.11.2025.
//

#include "village.hpp"

#include <cmath>

#include <tracy/Tracy.hpp>

#include <tools/random_engine.hpp>
#include <tools/logger.hpp>
#include <village/village_config.hpp>
#include <village/residents/resident_factory.hpp>
#include <village/entities_registry.hpp>

namespace vsa {
namespace village {

Village::Village(std::vector<std::shared_ptr<Resident>> residents):m_residents(residents) {
    m_residents_f.reserve(m_residents.size()/2);
    m_residents_m.reserve(m_residents.size()/2);

    for(auto res : m_residents) {
        if(res->is_male()) { m_residents_m.push_back(res); }
        else { m_residents_f.push_back(res); }
    }
}

sim::SimulationDataPoint Village::iterate()
{
    //
    // Consume (collect requirements)
    // Eat
    // Produce

    for (std::size_t i = 0; i < m_residents.size(); ++i) {
        {
            ZoneScopedN("Global Sim Iterate");
            auto& resident = m_residents.at(i);
            resident->iterate();
        }
    }

    for (auto& res : m_residents) {
        if(res->is_dead()) { res->remove_relations(); }
    }

    std::erase_if(m_residents, [](const std::shared_ptr<Resident>& r) { return r->is_dead(); });
    std::erase_if(m_residents_m, [](const std::shared_ptr<Resident>& r) { return r->is_dead(); });
    std::erase_if(m_residents_f, [](const std::shared_ptr<Resident>& r) { return r->is_dead(); });
    std::erase_if(m_couples, [](const auto& r) { return r.first->is_dead() || r.second->is_dead(); });

    if(tools::RandomEngine::get_instance().get_random_bool(VillageConfig::get_config().population.couple_creation_probability_per_day)) {
        auto f = m_residents_f[tools::RandomEngine::get_instance().get_random_uint(0, m_residents_f.size() - 1)];
        auto m = m_residents_m[tools::RandomEngine::get_instance().get_random_uint(0, m_residents_m.size() - 1)];

        if(!f->has_spouse() && !m->has_spouse() &&
            f->get_age_years() >= VillageConfig::get_config().population.min_couple_age &&
            m->get_age_years() >=  VillageConfig::get_config().population.min_couple_age &&
            std::abs(static_cast<std::int64_t>(f->get_age_years() - m->get_age_years())) <= VillageConfig::get_config().population.diference_couple_age) { 
                VSA_LOG_INFO("village", "Couple creation initialized.");
                f->add_spouse(m);
                m->add_spouse(f);
                m_couples.push_back({m, f});
        }
    }

    if(m_couples.size() > 0 && tools::RandomEngine::get_instance().get_random_bool(VillageConfig::get_config().population.child_creation_probability_per_day)) {
        auto p = m_couples[tools::RandomEngine::get_instance().get_random_uint(0, m_couples.size() - 1)];
        const auto& residents_ids = village::EntitiesRegistry::get_instance().get_residents_ids();
        auto c = village::ResidentFactory::create_resident(
                 residents_ids[tools::RandomEngine::get_instance().get_random_uint(0, residents_ids.size() - 1)],
                 tools::RandomEngine::get_instance().get_random_uint(0, 1), 0);
        if(p.first->is_male()) { c->add_father(p.first); c->add_mother(p.second); }
        else { c->add_mother(p.first); c->add_father(p.second); }
        p.first->add_child(c);
        p.second->add_child(c);
        if(c->is_male()) { m_residents_m.push_back(c); }
        else { m_residents_f.push_back(c); }
        m_residents.push_back(c);
    }

    // Generate statistics data
    sim::SimulationDataPoint p;
    p.m_population = m_residents.size();
    p.m_males = m_residents_m.size();
    p.m_females = m_residents_f.size();
    p.m_couples = m_couples.size();

    std::size_t count_of_resident_with_children = 0;

    for (const auto& resident : m_residents) {
        {
            ZoneScopedN("Global Sim Statistic");

            if(resident->get_children_count()) { count_of_resident_with_children++; }

            p.m_avg_age_years += resident->get_age_years();
            p.m_count_by_resident[resident->get_id()]++;
            p.m_avg_children_count += resident->get_children_count();
        }
    }
    p.m_avg_age_years /= m_residents.size() ? m_residents.size() : 1;
    p.m_avg_children_count_inclusive = 1.0 * p.m_avg_children_count / (count_of_resident_with_children ? count_of_resident_with_children : 1);
    p.m_avg_children_count /= 1.0 * (m_residents.size() ? m_residents.size() : 1);

    return p;
}

} // village
} // vsa