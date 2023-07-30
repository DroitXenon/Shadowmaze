#include "elf.h"

elf::elf():
    enemy_character{140, 30, 10, "Elf", 'E', true, -1} {}

int elf::attack(std::shared_ptr<player_character> player) {
    int damage = (int) ceil((100.0 / (100 + player->get_def())) * get_atk());
    if (player->get_race() != "drow") {
            damage = 2 * damage;
    }
    player->set_hp(player->get_hp() - damage);
    return damage; 
}
