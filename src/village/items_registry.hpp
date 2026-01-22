#pragma once

#include <map>
#include <string>

namespace vsa::village {

struct ItemInfo {
    std::string name;
    int         price;
};

class ItemsRegistry {
public:
    static ItemsRegistry& get_instance();

private:
    ItemsRegistry();

public:
    void register_item(const std::string& id,
                       const std::string& name,
                       int price);

    [[nodiscard]] std::map<std::string, ItemInfo> get_items() const;

private:
    std::map<std::string, ItemInfo> m_items;
};

template<typename T>
class ItemsRegistrator {
public:
    ItemsRegistrator() {
        auto& r = ItemsRegistry::get_instance();
        r.register_item(T::get_id(), T::get_name(), T::get_price());
    }
};

} // namespace vsa::village
