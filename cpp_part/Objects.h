#ifndef CPP_PART_OBJECTS_H
#define CPP_PART_OBJECTS_H
#include "math.h"
#include "global_const.h"
#include "iostream"

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Object: public Sprite{
protected:
    float x,y;
    float width, height;
    Texture texture_o;
public:
    Object(float x,float y, Texture texture_o){
        this->x = x;
        this->x = x;
        this->texture_o = texture_o;
    }
    Object(){};
    ~Object() = default;
    float get_x(){ return x;}
    float get_y(){ return y;}
};

class Player: public Object{
private:
    Image player_image;
    Texture player_texture;

    float speed = PLAYER_SPEED;

    /*Sprite player_sprite;
    double direction;
    float dx_speed, dy_speed;*/
    float rotate_speed=30*5*4;
public:
    Player(float x,float y, float width, float height){
        this->x = x;
        this->y = y;
        this->setPosition(x,y);
        this->setOrigin(tile_size/2,tile_size/2);
        //this->direction = 0;
        this->width = width;
        this->height = height;
        //Texture player_texture;
        //player_image.loadFromFile("E:\\final_project\\cpp_part\\images\\chel.png");
        //player_texture.loadFromImage(player_image);
        player_texture.loadFromFile(R"(E:\final_project\cpp_part\images\chel.png)",
                                    IntRect(0, 0, tile_size,tile_size));
        //player_texture.setSmooth(true);//сглаживание
        //setTexture(player_texture);
        this->setTexture(player_texture);
    }

    void change_dir(sf::Event event, float d_time){

        cout << this->getRotation() << endl;
    }

    /*
    void collision(const Player& p, sf::String minimap[MAP_y]) {
        for (unsigned int y = 0; y < MAP_y; y++) {
            for (unsigned int x = 0; x < minimap[y].getSize(); x++) {
                switch (minimap[y][x]) {
                    case Tiles_map::Wall: {
                        rectangle.setFillColor(sf::Color(30, 30, 200));
                        i_window.draw(rectangle);
                        minimap[y][x] = Tiles_map::Wall;
                    }
                    case ' ': {
                        minimap[y][x] = Tiles_map::Empty;
                    }

                }
            }
            for (const auto &wall: walls_) {
                if (p.getGlobalBounds().intersects(wall.getGlobalBounds())) {
                    std::cout << "COLLISIOON" << endl;
                }
            }
        }
    }

    */
    void go(sf::Event event,float d_time){
        //rotate
        if (event.key.code == sf::Keyboard::D){
            this->rotate(this->rotate_speed * d_time);
        }
        if (event.key.code == sf::Keyboard::A){
            this->rotate(- this->rotate_speed * d_time);
        }
        //go
        if (event.key.code ==(Keyboard::W)){

            this->move(speed*d_time*cos(this->getRotation()*PI/180),
                       speed*d_time*sin(this->getRotation()*PI/180));
        }

        if (event.key.code ==(Keyboard::S)){

            this->move(-speed*d_time*cos(this->getRotation()*PI/180),
                       -speed*d_time*sin(this->getRotation()*PI/180));
        }

        std::cout << this->getPosition().x <<"  "<< this->getPosition().y  << endl;
    }

    /*if(abs(x)==10 && abs(y)==10){
            this->move(x*speed*d_time*(1-cos(this->getRotation()*PI/180))/sqrt(2),
                       y*speed*d_time*(1-sin(this->getRotation()*PI/180))/sqrt(2));
        }*/

/*
    void move_anim(float d_time){

        switch(direction){
            case 0:
                dx_speed = speed; dy_speed = 0; break;
            case 1:
                dx_speed = -speed; dy_speed = 0; break;
            case 2:
                dx_speed = 0; dy_speed = speed; break;
            case 3:
                dx_speed = 0; dy_speed = -speed; break;
        }

        x += dx_speed*d_time;

        y += dy_speed*d_time;

        speed = 0;//персонаж остановился

        player_sprite.setPosition(x,y);//новая позция, переменпе
    }


    void move(float speed, float elapsed_time){
        if (Keyboard::isKeyPressed(Keyboard::A)){
            direction = 1;

            player_sprite.move(-speed*elapsed_time, 0);
            player_sprite.setTextureRect(IntRect(tile_size*6, 0, tile_size,tile_size));
        }
        //right
        if (Keyboard::isKeyPressed(Keyboard::D)){
            direction = 0;

            player_sprite.move(speed*elapsed_time, 0);
            player_sprite.setTextureRect(IntRect(tile_size*2, 0, tile_size,tile_size));

        }
        //up
        if (Keyboard::isKeyPressed(Keyboard::W)){
            direction = 3;

            player_sprite.move(0, -speed*elapsed_time);
            player_sprite.setTextureRect(IntRect(tile_size*4, 0, tile_size,tile_size));

        }
        //down
        if (Keyboard::isKeyPressed(Keyboard::S)){
            direction = 2;

            player_sprite.move(0, speed*elapsed_time);
            player_sprite.setTextureRect(IntRect(0, 0, tile_size,tile_size));
        }
    }

*/

};


#endif //CPP_PART_OBJECTS_H
