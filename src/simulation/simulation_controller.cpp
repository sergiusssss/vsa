#include "simulation_controller.hpp"

#include <mutex>
#include <utility>
#include <cstdlib>
#include <vector>

#include <tools/logger.hpp>

namespace vsa::sim {

SimulationController::SimulationController() {}

SimulationController::~SimulationController() {}

bool SimulationController::init()
{
    VSA_LOG_INFO("sim_ctrl", "Simulation Controller initialized.");
    return true;
}

bool SimulationController::deinit()
{
    VSA_LOG_INFO("sim_ctrl", "Simulation Controller deinitialized.");
    return true;
}

bool SimulationController::run()
{
    stop();
    m_should_stop.store(false);

    m_is_working.store(false);
    m_is_error.store(false);

    m_working_thread = std::thread(&SimulationController::working_thread, this);

    std::unique_lock lock(m_is_working_mtx);
    m_is_working_cv.wait(
      lock, [is_working = &m_is_working, is_error = &m_is_error]() { return is_working->load() || is_error->load(); });

    VSA_LOG_INFO("sim_ctrl", "Simulation Controller main loop inited.");
    return true;
}

void SimulationController::register_callback_listener(std::shared_ptr<CallbackListener> listener)
{
    std::lock_guard lg(m_listener_mtx);
    m_listeners.push_back(std::move(listener));
}

std::size_t SimulationController::simulate(const SimulationConfig& config)
{
    VSA_LOG_INFO("sim_ctrl", "New simulation initiated.");

    {
        std::lock_guard lg(m_simulations_queue_mtx);
        m_simulations_queue.push(config);
    }

    return 0;
}

void SimulationController::working_thread()
{
    {
        std::unique_lock lock(m_is_working_mtx);
        m_is_working.store(true);
        m_is_working_cv.notify_all();
    }

    VSA_LOG_INFO("sim_ctrl", "Simulation Controller main loop started.");

    while (!m_should_stop.load()) {
        std::unique_lock lock(m_simulations_queue_mtx);

        if (m_simulations_queue.empty()) { continue; }

        VSA_LOG_INFO("sim_ctrl", "New simulation request detected. Processing started.");

        SimulationConfig config = m_simulations_queue.front();
        m_simulations_queue.pop();

        lock.unlock();

        //std::this_thread::sleep_for(std::chrono::seconds(3));

        //std::vector<SimulationDataPoint> points(config.max_duration_days);

        // ... внутри while (!m_should_stop.load()) в методе working_thread ...

std::vector<SimulationDataPoint> points;
points.reserve(config.max_duration_days);//test

for (std::size_t day = 0; day < config.max_duration_days; ++day) {
    SimulationDataPoint point;
    
    
    point.m_population = 500 + (std::rand() % 500); 
    
    
    point.m_males = static_cast<std::size_t>(point.m_population * (config.population.percentage_of_men / 100.0f));//test
    point.m_females = point.m_population - point.m_males;
    
    
    int min_a = config.population.initial_min_age;
    int max_a = config.population.initial_max_age;
    point.m_average_age = static_cast<float>(min_a + (std::rand() % (max_a - min_a + 1)));//test
    
    
    for (const auto& [name, res_cfg] : config.residents) {
        point.m_profession_distribution[name] = static_cast<std::size_t>(point.m_population * res_cfg.initial_percentage);//test< m_profetion!!
    }

    points.push_back(std::move(point));//test
}


        SimulationData data(std::move(points));

       



       

        auto simulation = std::make_shared<Simulation>(config, data);

        {
            std::lock_guard lg(m_listener_mtx);
            for (auto l : m_listeners) {
                l->on_simulation(0, simulation);
            }
        }

        VSA_LOG_INFO("sim_ctrl", "New simulation processing finished.");
    }

    VSA_LOG_INFO("sim_ctrl", "Simulation Controller main loop finished.");
}

}