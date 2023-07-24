#include "elf.h"

elf::elf():
    enemy_character{140, 30, 10, "Elf", 'E', true} {}

int elf::attack(std::shared_ptr<player_character> player) {
    int damage = (int) ceil((100.0 / (100 + player->get_def())) * get_atk());
    int miss = rand() % 2;
    if (miss) {
        damage = 0;
        //add_action("Elf missed!");
    }
    player->set_hp(player->get_hp() - damage);
    if (player->get_race() != "drow") {
        miss = rand() % 2;
        if (!miss) {
            //add_action("Elf attacks again!");
            damage = (int) ceil((100.0 / (100 + player->get_def())) * get_atk());
            player->set_hp(player->get_hp() - damage);
        } else {
            //add_action("Elf missed, again!");
        }
    }
    return damage; 
}
