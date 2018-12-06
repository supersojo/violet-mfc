#include "abstract/direction.h"

namespace violet {
    namespace abstract {
        Direction Direction::NORTH(0, -1);
        Direction Direction::SOUTH(0, 1);
        Direction Direction::EAST(1, 0);
        Direction Direction::WEST(-1, 0);
    }
}