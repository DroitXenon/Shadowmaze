#include "drow.h"
#include <iostream>

drow::drow(): 
    player_character{150, 25, 15, "drow", 'd', 150} {}

int drow::attack(std::shared_ptr<enemy_character> enemy) {
    int damage = (int) ceil((100.0 / (100.0 + enemy->get_def())) * get_atk());
    enemy->set_hp(enemy->get_hp() - damage);
    return damage;  
}
