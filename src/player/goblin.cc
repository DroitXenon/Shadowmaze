#include "goblin.h"
#include <iostream>

goblin::goblin(): 
    player_character{110, 15, 20, "Goblin", 'g', 110} {}

int goblin::attack(std::shared_ptr<enemy_character> enemy) {
    int damage = (int) ceil((100.0 / (100.0 + enemy->get_def())) * get_atk());
     if (enemy->get_race() == "Halfling") {
        int miss = rand() % 2;
        if (miss) {
            damage = 0;
        } 
    }
    enemy->set_hp(enemy->get_hp() - damage);
    if (enemy->get_hp() <= 0) {
        set_hp(get_hp() + 5);
    }
    return damage;   
}
