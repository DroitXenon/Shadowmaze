#include "cell.h"

// cell::cell(char cell_type, std::string cell_name):
//     cell_type{cell_type},
//     cell_name{cell_name} {}

char cell::get_cell_type() const {
    return cell_type;
}

bool cell::get_step() const {
    return can_step;
}

void cell::set_cell_type(char cell_type) {
    this->cell_type = cell_type;
}

void cell::set_step(bool stepable) {
    this->can_step = stepable;
}
