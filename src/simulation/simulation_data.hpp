#pragma once

#include <vector>
#include <map>
#include <string>

namespace vsa::sim {

struct SimulationDataPoint
{
    std::size_t m_population = 0;
    std::size_t m_males = 0;
    std::size_t m_females = 0;
    std::size_t m_avg_age_years = 0;
    std::map<std::string, std::size_t> m_count_by_resident;
    std::size_t m_couples = 0;
    float m_avg_children_count = 0;
    float m_avg_children_count_inclusive = 0;
};

class SimulationData
{
public:
    explicit SimulationData(std::vector<SimulationDataPoint>&& points);

    [[nodiscard]] const std::vector<SimulationDataPoint>& get_points() const { return m_points; }
private:
    std::vector<SimulationDataPoint> m_points;
};

}
