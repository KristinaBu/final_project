//#ifndef CPP_PART_GLOBAL_CONST_H
//#define CPP_PART_GLOBAL_CONST_H
//
//#endif //CPP_PART_GLOBAL_CONST_H
//файл подключается к проекту единожды
#pragma once
//constexpr - значения константных выражений, которые могут быть вычислены во время компиляции кода
constexpr float PI = 3.141592653589793116f;

//плитка карты
constexpr unsigned int tile_size = 32;

constexpr unsigned int WINDOW_SIZE_X = 1280;
constexpr unsigned int WINDOW_SIZE_Y = 720;
constexpr unsigned int PLAYER_SPEED = tile_size;
constexpr float PLAYER_ROTATE_SPEED = PI / 4;
constexpr float PLAYER_FOV = PI / 2;
constexpr float FOG_LEVEL = 200;


enum Tiles_map {
    Empty,
    WallTile
};



