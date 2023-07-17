#ifndef MAP_H
#define MAP_H
#include <memory>
#include <iostream>
#include "player/player_character.h"

const int NUM_COL = 79;
const int NUM_ROW = 25;

class map {
    std::shared_ptr<player_character> player;
    //enemy
    //gold
    //posion
    int num_posion = 0;
    int num_gold = 0;
    int num_enemy = 0;


 public:
    void change_player(std::shared_ptr<player_character> pc);
    void set_map();
    void set_player();
    void set_stair();
    void set_posion();
    void set_gold();
    void set_enemy();


};




#endif