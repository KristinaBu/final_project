#ifndef CPP_PART_DIRECTION_H
#define CPP_PART_DIRECTION_H
#include "math.h"
#include <SFML/Graphics.hpp>


int n=-45;
float direction = fmod(360 + fmod(n,360),360);

//360/45 - 8 направлений

#endif //CPP_PART_DIRECTION_H
