#include "shade.h"
#include <iostream>

shade::shade(): 
    player_character{125, 25, 25, "shade", 's', 125} {}

void shade::attack(std::shared_ptr<enemy_character> enemy) {
    std::cout << "Player Attack!" <<std::endl;    
}