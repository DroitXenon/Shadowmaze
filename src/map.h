#ifndef MAP_H
#define MAP_H
#include <memory>
#include <iostream>
#include <fstream>
#include <vector>
#include "player/player_character.h"
#include "enemy/enemy_character.h"
#include "enemy/human.h"
#include "enemy/dwarf.h"
#include "enemy/elf.h"
#include "enemy/orc.h"
#include "enemy/merchant.h"
#include "enemy/dragon.h"
#include "enemy/halfling.h"
#include "pos.h"
#include "cell.h"


const int NUM_COL = 79;
const int NUM_ROW = 25;
#include <iostream>
#include <cstdlib>
#include <ctime>


class map {
    std::shared_ptr<player_character> player;
    std::vector<std::shared_ptr<enemy_character>> enemies;
    // std::vector<std::shared_ptr<posion>> posions;
    // std::vector<std::shared_ptr<gold>> golds;
  
    int num_posion = 0;
    int num_gold = 0;
    int num_enemy = 0;
    cell map_cell[NUM_COL][NUM_ROW];
    cell origin_map_cell[NUM_COL][NUM_ROW];
    std::vector<std::string> actions;
    bool gameover = false;


 public:
    void set_player(std::shared_ptr<player_character> pc);
    void set_map();
    void generate_player(int chamber_id);
    void generate_stair(int chamber_id);
    void generate_posion();
    void generate_gold();
    void generate_enemy();
    void read_empty_map(std::string& filename);
    void read_map_file(std::string& filename, int floor);
    void print_map();
    void move_player(std::string direction);
    void player_attack(std::string direction);
    void move_enemy();
    void enemy_attack();
    void use_potion(std::string& direction);
    bool is_adjacent(pos p1, pos p2);
    int which_enemy(int x, int y);
    int which_potion();
    pos direction_pos(std::string direction, pos current_pos);
    bool is_gameover();
    void set_gameover();
    void check_state();
};




#endif