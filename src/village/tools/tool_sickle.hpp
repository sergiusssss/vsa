

#pragma once
#include <string>
#include <village/tool.hpp>

namespace vsa::village {

class ToolSickle : public Tool
{
public:
    static std::string get_id() { return "tool_sickle"; }
    static std::string get_name() { return "Sickle"; }
    static int get_price() { return 25; } 
};

} // namespace vsa::village
