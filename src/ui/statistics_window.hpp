#pragma once
#include "ui/window.hpp"
#include "simulation/simulation.hpp"
#include "imgui.h"
#include <vector>
#include "simulation_controller.hpp"
#include "simulation_data.hpp"
#include "window.hpp"


namespace vsa::ui {
class StatisticsWindow : public Window {
public:
    void set_data(std::shared_ptr<sim::Simulation> sim) {
        m_simulation = sim;
        m_show_statistics = true;
    }
    void render() override {
        if (!m_show_statistics || !m_simulation) return;
        ImGui::Begin("Simulation Stats", &m_show_statistics);
        
        auto& points = m_simulation->get_data().get_points();
        std::vector<float> pop_values;
        for(auto& p : points) pop_values.push_back((float)p.m_population);

        ImGui::PlotLines("Population", pop_values.data(), pop_values.size(), 0, nullptr, 0.0f, 1000.0f, ImVec2(0, 100));
        
        static int day = 0;
        if (day >= points.size()) day = points.size() - 1;
        ImGui::SliderInt("Day Selector", &day, 0, points.size() - 1);
        ImGui::Text("Population on day %d: %zu", day, points[day].m_population);
        
        ImGui::End();
    }
private:
    bool m_show_statistics = false;
    std::shared_ptr<sim::Simulation> m_simulation;
};
}

