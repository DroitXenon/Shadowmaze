#include "troll.h"
#include <iostream>

troll::troll(): 
    player_character{120, 25, 15, "troll", 't', 120} {}

int troll::attack(std::shared_ptr<enemy_character> enemy) {
    int damage = (int) ceil((100.0 / (100.0 + enemy->get_def())) * get_atk());
    if (enemy->get_race() == "halfling") {
        int miss = rand() % 2;
        if (miss) {
            damage = 0;
        } 
    }
    set_hp(get_hp() + 5);
    if (get_hp() > get_max_hp()) {
        set_hp(get_max_hp());
    }
    enemy->set_hp(enemy->get_hp() - damage);
    return damage;   
}
