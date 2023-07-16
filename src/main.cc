#include <sstream>
#include "start.h"

int main(int argc, char *argv[]) {
    if (argc == 1) {
        start();
    } else if (argc == 2) {
        std::string map = argv[--argc];
        start_w_map(map);
    } else if (argc == 3) {
        std::string seed = argv[--argc];
        std::string map = argv[--argc];
        start_w_seed(map, seed);
    }
}
