#include <sstream>
#include "start.h"

int main(int argc, char *argv[]) {
    if (argc == 1) {
        start();
    } else if (argc == 2) {
        std::string map = argv[--argc];
        start(map, true);
    } else if (argc == 3) {
        std::string seed = argv[--argc];
        std::string map = argv[--argc];
        std::istringstream iss(seed);
        unsigned int seed_int = 0;
        iss >> seed_int;
        start(map, true, seed_int, true);
    }
}
