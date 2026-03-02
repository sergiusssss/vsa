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
        m_selected_day = 0;//test
    }
    void render() override {
        if (!m_show_statistics || !m_simulation) return;
        ImGui::Begin("Simulation Stats", &m_show_statistics);
        

        const auto& points = m_simulation->get_data().get_points();//test
        if (points.empty()) {
            ImGui::Text("No data available yet.");//test
            ImGui::End();
            return;
        }//test


        //auto& points = m_simulation->get_data().get_points();
        std::vector<float> pop_values;
        for(auto& p : points) pop_values.push_back((float)p.m_population);

        ImGui::PlotLines("Population", pop_values.data(), pop_values.size(), 0, nullptr, 0.0f, 1000.0f, ImVec2(0, 100));

        ImGui::Separator();//test
        std::vector<float> age_values;
        for(const auto& p : points) age_values.push_back(p.m_average_age);//test

        ImGui::Text("Average Age Distribution");
        ImGui::PlotHistogram("##Age", age_values.data(), age_values.size(), 0, nullptr, 0.0f, 100.0f, ImVec2(0, 80));//test

        ImGui::Separator();//test

        if (m_selected_day >= (int)points.size()) m_selected_day = (int)points.size() - 1;

        const auto& current_p = points[m_selected_day];
        
        ImGui::TextColored(ImVec4(1, 1, 0, 1), "Day %d (Year %d)", m_selected_day, m_selected_day / 365);//test
        ImGui::Text("Total Residents: %zu", current_p.m_population);
        ImGui::Text("Avg Age: %.1f years", current_p.m_average_age);
        ImGui::Text("Sex: %zu Male | %zu Female", current_p.m_males, current_p.m_females);//test

        if (!current_p.m_profession_distribution.empty()) {//test
            if (ImGui::TreeNode("Profession Stats")) {
                for (const auto& [name, count] : current_p.m_profession_distribution) {//test
                    ImGui::Text("%s: %zu", name.c_str(), count);
                }
                ImGui::TreePop();//test
            }
        }//test

        
        static int day = 0;
        if (day >= points.size()) day = points.size() - 1;
        ImGui::SliderInt("Day Selector", &day, 0, points.size() - 1);
        ImGui::Text("Population on day %d: %zu", day, points[day].m_population);
        
        ImGui::End();
    }
private:
    bool m_show_statistics = false;
    int m_selected_day = 0;//test
    std::shared_ptr<sim::Simulation> m_simulation;
};
}

