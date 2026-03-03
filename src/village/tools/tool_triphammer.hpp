

#pragma once
#include <string>
#include <village/tool.hpp>

namespace vsa::village {

class ToolTriphammer : public Tool
{
public:
    static std::string get_id() { return "tool_triphammer"; }
    static std::string get_name() { return "Trip Hammer"; }
    static int get_price() { return 150; } 
};

} // namespace vsa::village
