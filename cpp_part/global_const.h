//#ifndef CPP_PART_GLOBAL_CONST_H
//#define CPP_PART_GLOBAL_CONST_H
//
//#endif //CPP_PART_GLOBAL_CONST_H
//файл подключается к проекту единожды
#pragma once
//constexpr - значения константных выражений, которые могут быть вычислены во время компиляции кода
constexpr float PI = 3.141592653589793116f;

//плитка карты 16 пикселей
constexpr unsigned int tile_size = 32;

constexpr unsigned int MAP_x = 15;
constexpr unsigned int MAP_y = 8;
constexpr unsigned int WINDOW_SIZE_X = MAP_x * tile_size;
constexpr unsigned int WINDOW_SIZE_Y = MAP_y * tile_size;
constexpr unsigned int PLAYER_SPEED = tile_size * 1000;
constexpr float PLAYER_ROTATE_SPEED = PI / 4 * 1000;
constexpr float PLAYER_FOV = PI / 2;


//для карты
//эхх
enum Tiles_map {
    Empty,
    WallTile
};



