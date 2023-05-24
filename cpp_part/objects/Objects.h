#ifndef CPP_PART_OBJECTS_H
#define CPP_PART_OBJECTS_H

#include <cmath>
#include "../global_const.h"
#include "iostream"

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

enum Types {
    WallType, EnemyType, PickUpType
};

class Object {
private:
    Types type;
public:
    Object() = default;

    void set_type(Types Type) {
        type = Type;
    }

    Types get_type() {
        return type;
    }
};


#endif //CPP_PART_OBJECTS_H
