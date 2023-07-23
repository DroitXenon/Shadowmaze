#include "vampire.h"
#include <iostream>

vampire::vampire(): 
    player_character{50, 25, 25, "vampire", 'v', -1} {}

int vampire::attack(std::shared_ptr<enemy_character> enemy) {
    int damage = (int) ceil((100.0 / (100.0 + enemy->get_def())) * get_atk());
    int miss = rand() % 2;
    if (miss && enemy->get_race() == "halfling") {
        damage = 0;
    } else {
        set_hp(get_hp() + 5);
    }
    enemy->set_hp(enemy->get_hp() - damage);
    return damage;   
}
