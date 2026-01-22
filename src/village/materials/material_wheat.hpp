//
// Created by Serhii Pustovit on 30.11.2025.
//

#pragma once

#include <string>
#include <village/material.hpp>

namespace vsa::village {

class MaterialWheat : public Material {
public:
    static std::string get_id()   { return "material_wheat"; }
    static std::string get_name() { return "Wheat"; }
    static int        get_price() { return 3; }
};

} // namespace vsa::village

