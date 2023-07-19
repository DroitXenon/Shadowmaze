#ifndef MAP_H
#define MAP_H
#include <memory>
#include <iostream>
#include "player/player_character.h"
#include "pos.h"
#include "cell.h"
#include <fstream>
#include <iostream>
#include <vector>

const int NUM_COL = 79;
const int NUM_ROW = 25;
#include <iostream>
#include <cstdlib>
#include <ctime>

class map {
    std::shared_ptr<player_character> player;
    //enemy
    //gold
    //posion
    int num_posion = 0;
    int num_gold = 0;
    int num_enemy = 0;
    cell map_cell[NUM_COL][NUM_ROW];
    std::vector<std::string> actions;

 public:
    void set_player(std::shared_ptr<player_character> pc);
    void set_map();
    void generate_player(int chamber_id);
    void generate_stair(int chamber_id);
    void generate_posion();
    void generate_gold();
    void generate_enemy();
    void read_map(std::string& filename);
    void print_map();
    void move_player(std::string direction);
    void move_enemy();
    void use_potion(std::string& direction);
    bool is_adjacent();
    void add_action(std::string& action);

};




#endif