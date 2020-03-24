#include "player.h"
#include <iostream>

Player::~Player()
{
    std::cout << "Player " << id <<" wurde gelöscht" << std::endl;
}
