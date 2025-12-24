#include <village/entities_registry.hpp>

#include <village/residents/resident_baker.hpp>
#include <village/residents/resident_miner.hpp>
#include <village/residents/resident_blacksmith.hpp>

namespace vsa::village {

const ResidentRegistrator<ResidentBaker> registrator_baker;
const ResidentRegistrator<ResidentMiner> registrator_miner; 
const ResidentRegistrator<ResidentBlacksmith> registrator_blacksmith;
}