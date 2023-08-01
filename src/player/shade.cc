#include "shade.h"
#include <iostream>

shade::shade(): 
    player_character{125, 25, 25, "Shade", 's', 125} {}

int shade::attack(std::shared_ptr<enemy_character> enemy) {
    //std::cout << "Player Attack!" <<std::endl;
    int damage = (int) ceil((100.0 / (100.0 + enemy->get_def())) * get_atk());
    //std::cout << "Player damage: " << damage << std::endl;
    if (enemy->get_race() == "Halfling") {
        int miss = rand() % 2;
        if (miss) {
            damage = 0;
        } 
    }
    enemy->set_hp(enemy->get_hp() - damage);
    return damage;
}
