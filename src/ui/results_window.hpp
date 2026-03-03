#pragma once

#include "window.hpp"
#include "simulation.hpp"
#include <imgui_neo_internal.h>
#include "imgui_neo_sequencer.h"
#include "simulation_config.hpp"
#include "simulation_controller.hpp"
#include "simulation_data.hpp"
#include "imgui.h"
#include <vector>

namespace vsa::ui {

class ResultsWindow : public Window
{
public:
    void set_data(std::shared_ptr<sim::Simulation> sim) {
        m_simulation = sim;
        m_is_open = true;
    }

    void render() override {
        if (!m_is_open || !m_simulation) return;

        ImGui::Begin("Simulation Results", &m_is_open);

        const auto& points = m_simulation->get_data().get_points();
        
        
        std::vector<float> plot_data;
        for (const auto& p : points) {
            plot_data.push_back(static_cast<float>(p.m_population));
        }

        
        ImGui::Text("Population dynamics");
        ImGui::PlotLines("##PopulationGraph", plot_data.data(), plot_data.size(), 0, nullptr, 0.0f, 500.0f, ImVec2(0, 150));

        ImGui::Separator();

        
        static int selected_day = 0;
        if (selected_day >= (int)points.size()) selected_day = (int)points.size() - 1;

        ImGui::SliderInt("Time Point (Day)", &selected_day, 0, (int)points.size() - 1);

        
        ImGui::Value("Population on this day", (unsigned int)points[selected_day].m_population);

        ImGui::End();
    }

private:
    bool m_is_open = false;
    std::shared_ptr<sim::Simulation> m_simulation;
};

}