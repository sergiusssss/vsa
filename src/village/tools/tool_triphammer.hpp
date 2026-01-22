//
// Created by Serhii Pustovit on 30.11.2025.
//

#pragma once

#include <string>
#include <village/tool.hpp>

namespace vsa::village {

class ToolTriphammer : public Tool {
public:
    static std::string get_id()   { return "tool_triphammer"; }
    static std::string get_name() { return "Triphammer"; }
    static int        get_price() { return 25; }
};

} // namespace vsa::village

