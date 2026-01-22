#include "items_registry.hpp"

namespace vsa::village {

ItemsRegistry& ItemsRegistry::get_instance() {
    static ItemsRegistry instance;
    return instance;
}

ItemsRegistry::ItemsRegistry() = default;

void ItemsRegistry::register_item(const std::string& id,
                                  const std::string& name,
                                  int price) {
    m_items[id] = { name, price };
}

std::map<std::string, ItemInfo> ItemsRegistry::get_items() const {
    return m_items;
}

} // namespace vsa::village
