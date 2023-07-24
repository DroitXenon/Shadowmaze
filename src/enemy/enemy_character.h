#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include <vector>
#include "../character.h"
#include "../pos.h"
#include "../player/player_character.h"


class player_character;
class enemy_character: public character {
    std::vector<int> drop_item;
    bool active = true;
    bool hostile;
    bool moved;
    int dragon_hoard_id;
 public:
    enemy_character(int hp, int atk, int def, std::string race, char symbol, bool hostile);
    std::vector<int> get_drop_item() const;
    bool is_active() const;
    bool is_hostile() const;
    // void set_drop_item(std::vector<int> item_index);
    void set_active(bool active);
    void set_hostile(bool hostile);
    int get_dragon_hoard_id();
    void set_dragon_hoard_id(int id);
    
    void set_moved(bool moved);
    bool is_moved();
    virtual int attack(std::shared_ptr<player_character> player) = 0;
    // virtual void attacked() = 0;
    
};

#endif
