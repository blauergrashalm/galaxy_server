#include "player.hpp"
#include <iostream>
#include "debug_functions.hpp"

Player::~Player()
{
    DBG_LOG(LOW, "Player " + std::to_string(id) + " wurde gelöscht");
}

nlohmann::json Player::toJson()
{
    nlohmann::json result;
    result["name"] = name;
    result["id"] = id;
    result["type"] = "player";
    return result;
}
