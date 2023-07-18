#include "map.h"

void map::set_player(std::shared_ptr<player_character> character){
    player = character;
    //std::cout << "player set" << std::endl;
}

void map::set_map(){
    int chamber_id_player = rand() % 5 + 1;
    int chamber_id_stair = rand() % 5 + 1;
    while (chamber_id_stair == chamber_id_player) {
        chamber_id_player = rand() % 5 + 1;
       chamber_id_stair = rand() % 5 + 1;
    }
    std::cout << "chamber id generated " << chamber_id_player << std::endl;
    generate_player(chamber_id_player);
    //std::cout << "player generated" << std::endl;
    //generate_stair(chamber_id);
    //generate_posion();
    //generate_gold();
    //generate_enemy();
}

void map::generate_player(int chamber_id) {
    pos p;
    p.randomize_pos(chamber_id);
    std::cout << "player pos generated" << " " << p.get_x() << " " << p.get_y() << std::endl;
    std::cout << map_cell[p.get_x()][p.get_y()].get_cell_type() << std::endl;
    while (true) {
        if (map_cell[p.get_x()][p.get_y()].get_cell_type() == '.') {
        player->set_pos(p);
        map_cell[p.get_x()][p.get_y()].set_cell_type('@');
        map_cell[p.get_x()][p.get_y()].set_cell_name("player");
        break;
        } else {
            p.randomize_pos(chamber_id);
        }
    }
}

void map::generate_stair(int chamber_id) {

}

void map::generate_posion() {

}

void map::generate_gold() {

}

void map::generate_enemy() {
 
}

void map::read_map(std::string& filename) {
    std::ifstream map_file{filename};
    std::string line;
    int row = 0;
    while (getline(map_file, line)) {
        for (int i = 0; i < NUM_COL; ++i) {
            map_cell[i][row].set_cell_type(line[i]);
        }
        ++row;
    }
}




void map::print_map() {
    for (int i = 0; i < NUM_ROW; ++i) {
        for (int j = 0; j < NUM_COL; ++j) {
            std::cout << map_cell[j][i].get_cell_type();
        }
        std::cout << std::endl;
    }
}


