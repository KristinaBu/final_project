#ifndef CPP_PART_PLAYER_H
#define CPP_PART_PLAYER_H


#include <cmath>
#include "global_const.h"
#include "iostream"
#include "Objects.h"
#include "Wall.h"

#include <SFML/Graphics.hpp>
#include "map.h"
#include "Point.h"

class Player {
private:
    float speed = PLAYER_SPEED;
    float x, y;
    Image p_image;
    Texture p_texture;
    Sprite p_sprite;
    // радианы
    double direction = 0;
    float rotate_speed = PLAYER_ROTATE_SPEED;
    std::map<sf::Keyboard::Key, bool> key_state;
public:
    float get_x() const { return this->x; }

    float get_y() const { return this->y; }


    Player(float x, float y) {
        this->x = x;
        this->y = y;
        direction = 0;
        p_image.loadFromFile(R"(assets\kotokrolik.jpg)");
        p_texture.loadFromImage(p_image);
        p_sprite.setTexture(p_texture);

        p_sprite.setScale((float) tile_size / (float) p_texture.getSize().x,
                          (float) tile_size / (float) p_texture.getSize().y);

        this->p_sprite.setOrigin((float) p_texture.getSize().x / 2, (float) p_texture.getSize().y / 2);
        this->p_sprite.setPosition(x, y);

        key_state[sf::Keyboard::W] = false;
        key_state[sf::Keyboard::A] = false;
        key_state[sf::Keyboard::S] = false;
        key_state[sf::Keyboard::D] = false;
    }

    Sprite getSprite() {
        return p_sprite;
    }

    void set_key(sf::Keyboard::Key b, bool pressed) {
        this->key_state[b] = pressed;
    }

    double get_direction() const { return this->direction; }


//!!!!!!!!!!!!!!!!!!
    void go(float d_time, const std::vector<Object *> &objects_in_game) {
        d_time *= 100; //магия

        if (key_state[sf::Keyboard::W])
            move((float) (x + speed * d_time * cos(direction)),
                 (float) (y + speed * d_time * sin(direction)),
                 objects_in_game);
        if (key_state[sf::Keyboard::A]) direction -= rotate_speed * d_time;
        if (key_state[sf::Keyboard::S])
            move((float) (x - speed * d_time * cos(direction)),
                 (float) (y - speed * d_time * sin(direction)),
                 objects_in_game);
        if (key_state[sf::Keyboard::D]) direction += rotate_speed * d_time;

        this->p_sprite.setRotation((float) direction * 180 / PI);
    }

    void move(float X, float Y, const std::vector<Object *> &objects_in_game) {

        for (Object *obj: objects_in_game) {
            if (obj->get_type() == WallType) {
                Wall *p_wall = reinterpret_cast<Wall *>(obj);
                if (Wall::intersection(p_wall->get_x1(),
                                       p_wall->get_y1(),
                                       p_wall->get_x2(),
                                       p_wall->get_y2(),
                                       this->x, this->y, X, Y) != nullptr) {
                    return;
                }
            }
        }

        this->p_sprite.setPosition(X, Y);
        this->x = X;
        this->y = Y;
    }
};

#endif //CPP_PART_PLAYER_H
