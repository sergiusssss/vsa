#include "resident_blacksmith.hpp"

#include <iostream>

namespace vsa::village {

ResidentBlacksmith::ResidentBlacksmith(bool is_male, std::size_t age_days) : Resident(is_male, age_days) {}

void vsa::village::ResidentBlacksmith::eat()
{
    std::cout << "ResidentBlacksmith eat" << std::endl;
}

} // village
