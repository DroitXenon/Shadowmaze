#include "map.h"

void map::set_player(std::shared_ptr<player_character> character){
    player = character;
    actions.emplace_back("Player character has spawned.");
    //std::cout << "player set" << std::endl;
}

void map::set_map(){
    int chamber_id_player = rand() % 5 + 1;
    int chamber_id_stair = rand() % 5 + 1;
    while (chamber_id_stair == chamber_id_player) {
        chamber_id_player = rand() % 5 + 1;
       chamber_id_stair = rand() % 5 + 1;
    }
    std::cout << "player chamber id generated " << chamber_id_player << std::endl;
    std::cout << "stair chamber id generated " << chamber_id_stair << std::endl;
    generate_player(chamber_id_player);
    std::cout << "player generated" << std::endl;
    generate_stair(chamber_id_stair);
    std::cout << "stair generated" << std::endl;
    generate_posion();
    generate_gold();
    generate_enemy();
}

void map::generate_player(int chamber_id) {
    pos p;
    p.randomize_pos(chamber_id);
    //std::cout << map_cell[p.get_x()][p.get_y()].get_cell_type() << std::endl;
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
    std::cout << "player pos generated" << " " << p.get_x() << " " << p.get_y() << std::endl;
}

void map::generate_stair(int chamber_id) {
    pos p;
    p.randomize_pos(chamber_id);
    while (true) {
        if (map_cell[p.get_x()][p.get_y()].get_cell_type() == '.') {
            map_cell[p.get_x()][p.get_y()].set_cell_type('\\');
            map_cell[p.get_x()][p.get_y()].set_cell_name("stair");
            break;
        } else {
            p.randomize_pos(chamber_id);
        }
    }
    std::cout << "stair pos generated" << " " << p.get_x() << " " << p.get_y() << std::endl;
}

void map::generate_posion() {
    while (num_posion < 10) {
        pos p;
        p.randomize_pos();
        while (true) {
            if (map_cell[p.get_x()][p.get_y()].get_cell_type() == '.') {
                map_cell[p.get_x()][p.get_y()].set_cell_type('P');
                map_cell[p.get_x()][p.get_y()].set_cell_name("potion");
                break;
            } else {
                p.randomize_pos();
            }
        }
        ++num_posion;
    }
    std::cout << "potion generated" << std::endl;
}

void map::generate_gold() {
    while (num_gold < 10) {
        pos p;
        p.randomize_pos();
        while (true) {
            if (map_cell[p.get_x()][p.get_y()].get_cell_type() == '.') {
                map_cell[p.get_x()][p.get_y()].set_cell_type('G');
                map_cell[p.get_x()][p.get_y()].set_cell_name("gold");
                break;
            } else {
                p.randomize_pos();
            }
        }
        ++num_gold;
    }
    std::cout << "gold generated" << std::endl;
}

void map::generate_enemy() {
    while (num_enemy < 20) {
        pos p;
        p.randomize_pos();
        while (true) {
            if (map_cell[p.get_x()][p.get_y()].get_cell_type() == '.') {
                map_cell[p.get_x()][p.get_y()].set_cell_type('E');
                map_cell[p.get_x()][p.get_y()].set_cell_name("enemy");
                break;
            } else {
                p.randomize_pos();
            }
        }
        ++num_enemy;
    }
    std::cout << "enemy generated" << std::endl;
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
    std::cout << "Race: " << player->get_race() << " Gold: " << player->get_gold() << std::endl;
    std::cout << "HP: " << player->get_hp() << std::endl;
    std::cout << "Atk: " << player->get_atk() << std::endl;
    std::cout << "Def: " << player->get_def() << std::endl;
    std::cout << "Action: ";
    for (auto action : actions) {
        std::cout << action;
    }
    std::cout << std::endl;
    actions.clear();
}


