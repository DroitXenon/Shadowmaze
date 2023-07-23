#include "item.h"

item::item(char symbol):
    symbol{symbol} {}

item::~item() {}

std::string item::get_name() {
    return name;
}

char item::get_symbol() const {
    return symbol;
}

bool item::is_pickable() {
    return pickable;
}

void item::set_pickable(bool val) {
    pickable = val;
}

pos item::get_pos() {
    return position;
}

void item::set_pos(pos position) {
    this->position = position;
}

void item::set_name(std::string name) {
    this->name = name;
}

