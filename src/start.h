#ifndef START_H
#define START_H
#include <iostream>
#include <memory.h>
#include <fstream>
#include "character.h"
#include "player/shade.h"
#include "player/drow.h"
#include "player/vampire.h"
#include "player/troll.h"
#include "player/goblin.h"
#include "pos.h"
#include "map.h"
#define ESC "\033["
#define LIGHT_BLUE_BKG "106"
#define RED_TXT "31"
#define GREEN_TXT "32"
#define YELLOW_TXT "33"
#define BLUE_TXT "34"
#define PURPLE_TXT "35"
#define CYAN_TXT "36"
#define RESET "\033[m"

void start(std::string map_file = "cc3k-emptySingleFloor.txt", bool with_map = false, unsigned int seed_int = time(0),  bool with_seed = false);

#endif
