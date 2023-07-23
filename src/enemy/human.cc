#include "human.h"

human::human():
    enemy_character{140, 20, 20, "Human", 'H', true} {}

int human::attack(std::shared_ptr<player_character> player) {
    //std::cout << "Human attacks!" << std::endl;
    int damage = (int) ceil((100.0 / (100 + player->get_def())) * get_atk());
    //std::cout << "human damage: " << damage << std::endl;
    player->set_hp(player->get_hp() - damage);
    return damage;
}
