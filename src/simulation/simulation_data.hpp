#pragma once

#include <vector>

namespace vsa::sim {

struct SimulationDataPoint
{
    std::size_t m_population;
    float m_average_age;
    std::size_t m_males;
    std::size_t m_females;
    
    std::map<std::string, std::size_t> m_profession_distribution;
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
