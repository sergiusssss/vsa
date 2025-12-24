#include <string>

#ifndef VILLAGE_RESIDENT_MINER_HPP
#define VILLAGE_RESIDENT_MINER_HPP

class ResidentMiner
{
public:
    static std::string get_id() { return "resident_miner"; }
    static std::string get_name() { return "Miner"; }
};

#endif // VILLAGE_RESIDENT_MINER_HPP
