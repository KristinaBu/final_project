#ifndef CPP_PART_MAP_H
#define CPP_PART_MAP_H


#include <variant>
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "global_const.h"
#include "string"
#include "Objects.h"
#include "Wall.h"

using namespace sf;

class Map{
private:
    std::vector<std::vector<int>> minimap;
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    std::vector<Object> objects_in_game;
public:
    //!!!!!!!!!!!!!!!!
    std::vector<Object> get_objects_in_game(){
        return objects_in_game;
    }

    Map(std::vector<std::vector<int>> minimap){
        this->minimap = std::move(minimap);

        for(unsigned int y=0; y<MAP_y; y++){
            for(unsigned int x=0; x < this->minimap[y].size() ; x++){
                if (this->minimap[y][x] == 1){
                    class Wall wall1(x*tile_size, y*tile_size,x*tile_size+tile_size, y*tile_size),
                            wall2(x*tile_size+tile_size, y*tile_size,x*tile_size+tile_size, y*tile_size+tile_size),
                            wall3(x*tile_size, y*tile_size,x*tile_size, y*tile_size+tile_size),
                            wall4(x*tile_size, y*tile_size+tile_size,x*tile_size+tile_size, y*tile_size+tile_size);
                    Object obj;
                    obj.set(x*tile_size, y*tile_size,x*tile_size+tile_size, y*tile_size,Wall_);
                    objects_in_game.push_back(obj);
                    obj.set(x*tile_size+tile_size, y*tile_size,x*tile_size+tile_size, y*tile_size+tile_size, Wall_);
                    objects_in_game.push_back(obj);
                    obj.set(x*tile_size+tile_size, y*tile_size,x*tile_size+tile_size, y*tile_size+tile_size,Wall_);
                    objects_in_game.push_back(obj);
                    obj.set(x*tile_size+tile_size, y*tile_size,x*tile_size+tile_size, y*tile_size+tile_size,Wall_);
                    objects_in_game.push_back(obj);
                    /*objects_in_game.push_back(wall1);
                    objects_in_game.push_back(wall2);
                    objects_in_game.push_back(wall3);
                    objects_in_game.push_back(wall4);*/
                    this->minimap[y][x] = Tiles_map::Wall;
                }
                else if (this->minimap[y][x] == 0){
                    this->minimap[y][x] = Tiles_map::Empty;
                }
            }
        }
    }

    void draw(sf::RenderWindow& i_window){
        //sf::RectangleShape rectangle(sf::Vector2f(tile_size, tile_size));
        for(unsigned int y=0; y<MAP_y; y++){
            for(unsigned int x=0; x < minimap[y].size() ; x++){
                //rectangle.setPosition(x*tile_size, y*tile_size);
                if (minimap[y][x] == 1){
                    sf::VertexArray draw_walls(sf::Quads, 4);

                    draw_walls[0].position = sf::Vector2f(x*tile_size, y*tile_size);
                    draw_walls[1].position = sf::Vector2f(x*tile_size+tile_size, y*tile_size);
                    draw_walls[2].position = sf::Vector2f(x*tile_size+tile_size, y*tile_size+tile_size);
                    draw_walls[3].position = sf::Vector2f(x*tile_size, y*tile_size+tile_size);
                    i_window.draw(draw_walls);
                    /*rectangle.setFillColor(sf::Color(220,30,200));
                    i_window.draw(rectangle);*/
                }
                else if (minimap[y][x] == 0){
                    minimap[y][x] = Tiles_map::Empty;
                }

            }
        }
    }

};

/*

class new_map{
public:

    std::vector <std::vector<sf::RectangleShape>> makemap(const int* map_list,unsigned int width_x, unsigned int height_y){
        //int n=0;
        std::vector <std::vector<sf::RectangleShape>> walls;
        for (unsigned int xx = 0; xx < width_x; xx++)
            for (unsigned int yy = 0; yy < height_y; yy++){

                //walls[xx].emplace_back(sf::RectangleShape(tile_size, tile_size));
                walls[xx][yy].setPosition(xx*tile_size, yy*tile_size);
                walls[xx][yy].setFillColor(Color::White);
            }

        return walls;
    }

};
class TileMap : public sf::Drawable, public sf::Transformable
{
public:

    bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height)
    {
        // load the tileset texture
        if (!m_tileset.loadFromFile(tileset))
            return false;

        // resize the vertex array to fit the level size
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(width * height * 4);

        // populate the vertex array, with one quad per tile
        for (unsigned int xx = 0; xx < width; ++xx)
            for (unsigned int yy = 0; yy < height; ++yy)
            {
                // get the current tile number
                int tileNumber = tiles[xx + yy * width];

                // find its position in the tileset texture
                int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
                int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

                // get a pointer to the current tile's quad
                sf::Vertex* quad = &m_vertices[(xx + yy * width) * 4];

                // define its 4 corners
                quad[0].position = sf::Vector2f(xx * tileSize.x, yy * tileSize.y);
                quad[1].position = sf::Vector2f((xx + 1) * tileSize.x, yy * tileSize.y);
                quad[2].position = sf::Vector2f((xx + 1) * tileSize.x, (yy + 1) * tileSize.y);
                quad[3].position = sf::Vector2f(xx * tileSize.x, (yy + 1) * tileSize.y);

                // define its 4 texture coordinates
                quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
                quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
                quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            }

        return true;
    }

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &m_tileset;

        // draw the vertex array
        target.draw(m_vertices, states);
    }

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};

class TileMap11
{
private:
    sf::String minimap[MAP_y] = {
            "5111111111",
            "0011111111",
            "1111111111",
            "1111111111",
            "1110001111",
            "1111111111",
    };
    Image map_image1;
    Texture map_texture1;
    Sprite map_sprite1;
public:
    TileMap11(){
        sf::String minimap1[MAP_y];
        sf::String minimap0[MAP_y] = {
                "1111111111",
                "0011111111",
                "1111111111",
                "1111111111",
                "1110001111",
                "1111111111",
        };
        for(int i; i< MAP_y; i++)
            for(int j; j< MAP_x; j++) minimap1[i][j] = minimap0[i][j];

        map_image1.loadFromFile("E:\\final_project\\cpp_part\\images\\mapp.png");
        map_texture1.loadFromImage(map_image1);
        map_sprite1.setTexture(map_texture1);
    }

    Sprite map_draw(){
        TileMap11 m;
        sf::String minimap0[MAP_y] = {
                "1111111111",
                "0011111111",
                "1111111111",
                "1111111111",
                "1110001111",
                "1111111111",
        };
        for(int i; i< MAP_y; i++)
            for(int j; j< MAP_x; j++)
                m.minimap[i][j] = minimap0[i][j];

        for(int i=0; i< MAP_y; i++)
            for(int j=0; j< MAP_x; j++) {
                //HEEEEEEELP
               //int n = minimap[i][j];
               //map_sprite1.setTextureRect(Rect(n * 32, 0, 32, 32));
                switch (2-1) {
                    case '0':
                        map_sprite1.setTextureRect(Rect(0, 0, 32, 32));
                        break;
                    case '1':
                        map_sprite1.setTextureRect(Rect(32, 0, 32, 32));
                        break;

                }
                //if()

               map_sprite1.setPosition(j * 32, i * 32);

            }
        return map_sprite1;
    }
};


class Minimap{
public:

};

*/

#endif //CPP_PART_MAP_H
