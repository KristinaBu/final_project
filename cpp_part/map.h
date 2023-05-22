#ifndef CPP_PART_MAP_H
#define CPP_PART_MAP_H


#include <variant>
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "../global_const.h"
#include "string"
#include "objects/Objects.h"
#include "objects/Wall.h"

using namespace sf;

class Map {
private:
    std::vector<std::vector<int>> minimap;
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    std::vector<Object *> objects_in_game;
public:
    //!!!!!!!!!!!!!!!!
    std::vector<Object *> get_objects_in_game() {
        return objects_in_game;
    }

    explicit Map(std::vector<std::vector<int>> minimap) {
        this->minimap = std::move(minimap);

        for (unsigned int y = 0; y < MAP_y; y++) {
            for (unsigned int x = 0; x < this->minimap[y].size(); x++) {
                if (this->minimap[y][x] == 1) {
                    objects_in_game.push_back(
                            new Wall((float) x * tile_size, (float) y * tile_size, (float) x * tile_size + tile_size,
                                     (float) y * tile_size));
                    objects_in_game.push_back(new Wall((float) x * tile_size + tile_size, (float) y * tile_size,
                                                       (float) x * tile_size + tile_size,
                                                       (float) y * tile_size + tile_size));
                    objects_in_game.push_back(
                            new Wall((float) x * tile_size, (float) y * tile_size, (float) x * tile_size,
                                     (float) y * tile_size + tile_size));
                    objects_in_game.push_back(new Wall((float) x * tile_size, (float) y * tile_size + tile_size,
                                                       (float) x * tile_size + tile_size,
                                                       (float) y * tile_size + tile_size));
                    this->minimap[y][x] = Tiles_map::WallTile;
                } else if (this->minimap[y][x] == 0) {
                    this->minimap[y][x] = Tiles_map::Empty;
                }
            }
        }
    }

    void draw(sf::RenderWindow &i_window) {
        for (unsigned int y = 0; y < MAP_y; y++) {
            for (unsigned int x = 0; x < minimap[y].size(); x++) {
                if (minimap[y][x] == 1) {
                    sf::VertexArray draw_walls(sf::Quads, 4);
                    draw_walls[0].position = sf::Vector2f((float) x * tile_size, (float) y * tile_size);
                    draw_walls[1].position = sf::Vector2f((float) x * tile_size + tile_size, (float) y * tile_size);
                    draw_walls[2].position = sf::Vector2f((float) x * tile_size + tile_size,
                                                          (float) y * tile_size + tile_size);
                    draw_walls[3].position = sf::Vector2f((float) x * tile_size, (float) y * tile_size + tile_size);
                    i_window.draw(draw_walls);
                } else if (minimap[y][x] == 0) {
                    minimap[y][x] = Tiles_map::Empty;
                }

            }
        }
    }

};

#endif //CPP_PART_MAP_H
