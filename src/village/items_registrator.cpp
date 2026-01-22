#include "items_registry.hpp"
#include "dishes/dish_bread.hpp"
#include "materials/material_wheat.hpp"
#include "materials/material_metal_ore.hpp"
#include "tools/tool_sickle.hpp"
#include "tools/tool_triphammer.hpp"

namespace vsa::village {

const static ItemsRegistrator<DishBread>        r_db;
const static ItemsRegistrator<MaterialWheat>    r_mw;
const static ItemsRegistrator<MaterialMetalOre> r_mmo;
const static ItemsRegistrator<ToolSickle>       r_ts;
const static ItemsRegistrator<ToolTriphammer>   r_tt;

} // namespace vsa::village
