#include "player.hpp"
#include <iostream>
#include "debug_functions.hpp"

Player::~Player()
{
    DBG_LOG(LOW, "Player " + std::to_string(id) + " wurde gelöscht");
}
