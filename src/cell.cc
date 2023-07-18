#include "cell.h"

// cell::cell(char cell_type, std::string cell_name):
//     cell_type{cell_type},
//     cell_name{cell_name} {}

std::string cell::get_cell_name() {
    return cell_name;
}
char cell::get_cell_type() {
    return cell_type;
}

void cell::set_cell_name(std::string cell_name) {
    this->cell_name = cell_name;
}

void cell::set_cell_type(char cell_type) {
    this->cell_type = cell_type;
}
