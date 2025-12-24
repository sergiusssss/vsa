#pragma once

#include <string>
#include <map>

namespace vsa::village {
class EntitiesRegistry
{

public:
    static EntitiesRegistry& get_instance();

    void register_resident(const std::string& id, const std::string& name);

    void register_tool(const std::string& id, const std::string& name);

    const std::map<std::string, std::string>& get_residents() const;

private:
    EntitiesRegistry();
    std::map<std::string, std::string> m_residents;
};

template <typename T>
class ResidentRegistrator
{
public:
    ResidentRegistrator()
    {
        auto& r = EntitiesRegistry::get_instance();
        r.register_resident(T::get_id(), T::get_name());
    }
};


template <typename T>
class ToolRegistrator{
public:
    ToolRegistrator()
    {
        auto& r = EntitiesRegistry::get_instance();
        r.register_tool(T::get_id(), T::get_name());
    }
};

}