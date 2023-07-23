#include "gold.h"

gold::gold() :
    item{'G'} {}

void gold::set_value(int value) {
    this->value = value;
}

int gold::get_value() {
    return value;
}
