#ifndef MAP_H
#define MAP_H
#include <memory>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <map>
#include "player/player_character.h"
#include "enemy/enemy_character.h"
#include "enemy/human.h"
#include "enemy/dwarf.h"
#include "enemy/elf.h"
#include "enemy/orc.h"
#include "enemy/merchant.h"
#include "enemy/dragon.h"
#include "enemy/halfling.h"
#include "item.h"
#include "potion.h"
#include "gold.h"

#include "pos.h"
#include "cell.h"

#define ESC "\033["
#define LIGHT_BLUE_BKG "106"
#define RED_TXT "31"
#define GREEN_TXT "32"
#define YELLOW_TXT "33"
#define BLUE_TXT "34"
#define PURPLE_TXT "35"
#define RESET "\033[m"

const int NUM_COL = 79;
const int NUM_ROW = 25;

class map {
    std::shared_ptr<player_character> player;
    std::vector<std::shared_ptr<enemy_character>> enemies;
    std::vector<std::shared_ptr<potion>> potions;
    std::vector<std::shared_ptr<gold>> golds;
  
    int num_potion = 0;
    int num_gold = 0;
    int num_enemy = 0;
    int floor = 1;
    bool floor_change = false;
    cell map_cell[NUM_COL][NUM_ROW];
    cell origin_map_cell[NUM_COL][NUM_ROW];
    std::vector<std::string> actions;
    bool gameover = false;
    std::map<int, std::string> direction_map { 
        {0,"so"}, 
        {1,"no"}, 
        {2,"ea"}, 
        {3,"we"}, 
        {4,"ne"}, 
        {5,"nw"}, 
        {6,"se"}, 
        {7,"sw"} 
        };

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
    int which_potion(int x, int y);
    int which_gold(int x, int y);
    pos direction_pos(std::string direction, pos current_pos);
    bool is_gameover();
    void set_gameover();
    bool get_floor_change();
    int get_floor();
    void drop_gold(std::shared_ptr<enemy_character> enemy);
    void find_around();
    void game_over();
};

#endif
