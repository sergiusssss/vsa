#ifndef VILLAGE_TOOL_SICKLE_HPP
#define VILLAGE_TOOL_SICKLE_HPP

#include <string>

namespace vsa {
namespace village {

class ToolSickle
{
public:
    static std::string get_id() { return "tool_sickle"; }
    static std::string get_name() { return "Sickle"; }
};

} // village
} // vsa

#endif // VILLAGE_TOOL_SICKLE_HPP
