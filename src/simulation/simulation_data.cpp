#include "simulation_data.hpp"


namespace vsa::sim {

SimulationData::SimulationData(std::vector<SimulationDataPoint>&& points, SimulationDataGlobal&& global)
    : m_points(std::move(points)), m_global(global) {}
}