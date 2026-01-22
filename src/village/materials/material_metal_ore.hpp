//
// Created by Serhii Pustovit on 30.11.2025.
//

#pragma once

#include <string>
#include <village/material.hpp>

namespace vsa::village {

class MaterialMetalOre : public Material {
public:
    static std::string get_id()   { return "material_metal_ore"; }
    static std::string get_name() { return "Iron Ore"; }
    static int        get_price() { return 10; }
};

} // namespace vsa::village


