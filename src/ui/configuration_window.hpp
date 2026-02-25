#pragma once

#include <functional>

#include <simulation/simulation_config.hpp>
#include <simulation/simulation_controller.hpp>
#include <ui/window.hpp>

#include "results_window.hpp"

#include "statistics_window.hpp"
 

namespace vsa::ui {

class ConfigurationWindow
  : public Window
  , public sim::SimulationController::CallbackListener
{
public:
    explicit ConfigurationWindow(std::function<void(const sim::SimulationConfig&)> start_simulation);
    ~ConfigurationWindow() override;

    void render_menu() override;
    void render() override;

    

    //std::shared_ptr<StatisticsWindow> m_stats_display = std::make_shared<StatisticsWindow>();//test

    void set_statistics_window(std::shared_ptr<StatisticsWindow> window) { //test
        m_stats_window = window;
    }

private:

    std::shared_ptr<StatisticsWindow> m_stats_window = std::make_shared<StatisticsWindow>();//test

    void on_simulation(std::size_t id, std::shared_ptr<sim::Simulation> simulation) override
    {
        m_is_simulation_running = false;
        //m_is_visible = false;

        if (m_stats_window) {
        m_stats_window->set_data(simulation);//test
    }

        std::shared_ptr<StatisticsWindow> m_stats_window = std::make_shared<StatisticsWindow>();//test

    }

private:
    std::function<void(const sim::SimulationConfig&)> m_start_simulation;

    bool m_is_visible = true;
    bool m_is_simulation_running = false;

    std::int32_t m_max_duration_value = 0;
    std::int32_t m_max_duration_option_index = 0;
    sim::SimulationConfig m_config;


};

} // ui
