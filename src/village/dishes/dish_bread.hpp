#pragma once

#include <string>
#include "../dish.hpp"

class DishBread : public dish
{
public:
    static std::string get_id()   { return "dish_bread"; }
    static std::string get_name() { return "Bread"; }
    static int        get_price() { return 5; }
};
