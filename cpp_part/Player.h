#ifndef CPP_PART_PLAYER_H
#define CPP_PART_PLAYER_H


#include "math.h"
#include "global_const.h"
#include "iostream"
#include "Objects.h"

#include <SFML/Graphics.hpp>
#include "map.h"
#include "Point.h"

class Player: public Object {
private:
    float speed = PLAYER_SPEED;
    float x, y;
    Image p_image;
    Texture p_texture;
    Sprite p_sprite;
    // радианы
    double direction = 0;
    float last_x, last_y;
    float rotate_speed = PLAYER_ROTATE_SPEED;
    std::map<sf::Keyboard::Key,bool> key_state;
public:
    float get_x(){ return this->x; }
    float get_y(){ return this->y; }


    Player(float x, float y) {
        this->x = x;
        this->y = y;
        direction=0;
        p_image.loadFromFile("C:\\Users\\krist\\CLionProjects\\final_project\\cpp_part\\pictures\\ozero.jpg");
        p_texture.loadFromImage(p_image);
        p_sprite.setTexture(p_texture);

        p_sprite.setScale((float) tile_size / (float) p_texture.getSize().x,
                          (float) tile_size / (float) p_texture.getSize().y);

        this->p_sprite.setOrigin((float)p_texture.getSize().x/2, (float)p_texture.getSize().y/2);
        this->p_sprite.setPosition(x,y);

        key_state[sf::Keyboard::W] = false;
        key_state[sf::Keyboard::A] = false;
        key_state[sf::Keyboard::S] = false;
        key_state[sf::Keyboard::D] = false;
    }

    Sprite getSprite(){
        return p_sprite;
    }

    void set_key(sf::Keyboard::Key b, bool pressed){
        this->key_state[b] = pressed;
    }

    double get_direction(){ return this->direction; }

    /*bool check_collision(const std::vector<Object>& objects_in_game){
        //player
        sf::CircleShape p_circle((float)tile_size/2);
        p_circle.setOrigin((float)p_texture.getSize().x/2, (float)p_texture.getSize().y/2);
        p_circle.setPosition(this->x, this->y);

        for(const Object& object : objects_in_game) {
            if (this->p_sprite.getGlobalBounds().intersects(object.getGlobalBounds())) {
                cout << "COLLISIOON" << endl;
                return true;
            }
        }
        return false;
    }*/

//!!!!!!!!!!!!!!!!!!
    void go(float d_time, const std::vector<Object>& objects_in_game){
        d_time *= 100; //магия

        if(key_state[sf::Keyboard::W]) move(this->x + speed*d_time*cos(direction),
                                            this->y + speed*d_time*sin(direction),objects_in_game);
        if(key_state[sf::Keyboard::A]) direction -= rotate_speed * d_time;
        if(key_state[sf::Keyboard::S]) move(this->x - speed*d_time*cos(direction),
                                            this->y - speed*d_time*sin(direction),objects_in_game);
        if(key_state[sf::Keyboard::D]) direction += rotate_speed * d_time;

        //!!!!!!!!!!!!
        this->p_sprite.setRotation(direction*180/PI);
        std::cout << d_time << std::endl;
        std::cout << this->x <<"  "<< this->y  << endl;
    }

    void move(float x, float y,const std::vector<Object>& objects_in_game){
        //
        for(Object obj: objects_in_game){
            //std::cout << (string)typeid(obj).name() << std::endl;
            if(obj.get_type() == Wall_){
                //создаем стену
                class Wall p_wall;
                p_wall = obj;
                /*class Wall* p_wall;
                p_wall = static_cast<class Wall*>(&obj);*/
                Point p(-10,-10);
                /*if(p_wall.intersection(5, 5, 10, 10, 10, 5, 10, 20) != p){
                    cout<< "COLLISIO0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000ON"<< endl;
                    return;
                }*/
                if(p_wall.intersection(p_wall.get_x1(), p_wall.get_y1(), p_wall.get_x2(), p_wall.get_y2(),
                                         this->x, this->y, x, y) != p){
                    cout << "COLLISIO0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000ON" << endl;
                    //this->speed = 40000;
                    return;

                }
            }
        }

        this->p_sprite.setPosition(x, y);
        this->x = x; this->y = y;
    }



    /*void change_dir(sf::Event event, float d_time){

        cout << this->getRotation() << endl;
    }

    *//*
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

    *//*
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
*/
};

#endif //CPP_PART_PLAYER_H
