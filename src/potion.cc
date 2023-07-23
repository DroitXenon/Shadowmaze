#include "potion.h"

potion::potion() :
    item{'P'} {}

bool potion::is_revealed() {
    return revealed;
}

void potion::set_revealed(bool val) {
    revealed = val;
}
