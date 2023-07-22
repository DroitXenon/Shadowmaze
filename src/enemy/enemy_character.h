#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include "../character.h"
#include "../pos.h"

class enemy_character: public character {
    std::string drop_item;
    bool active = true;
    bool hostile;
    bool moved;
 public:
    enemy_character(int hp, int atk, int def, std::string race, char symbol, bool hostile);
    std::string get_drop_item() const;
    bool is_active() const;
    bool is_hostile() const;
    void set_drop_item(std::string drop_item);
    void set_active(bool active);
    void set_hostile(bool hostile);
    virtual void attack() = 0;
    void set_moved(bool moved);
    bool is_moved();
    // virtual void attacked() = 0;
    
};

#endif
