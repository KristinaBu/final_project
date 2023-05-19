//
// Created by Karamel on 18.02.2023.
//
#include <iostream>
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "map.h"
#include "Objects.h"
#include "math.h"

#include "global_const.h"
using namespace sf;
using namespace std;


void collision(const Player& p, const vector <sf::RectangleShape>& walls_){
    for (const auto &wall: walls_) {
        if (p.getGlobalBounds().intersects(wall.getGlobalBounds())) {
            cout << "COLLISIOON"<< endl;
        }
    }
}
int main() {

    //сглаживание неровных и диагональных линий
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::String minimap[MAP_y] = {
            "1111111111",
            "1        1",
            "1        1",
            "1   1    1",
            "1   1    1",
            "1   1    1",
            "1        1",
            "1        1",
            "1        1",
            "1111111111",
    };

    sf::RenderWindow window(sf::VideoMode(MAP_x*tile_size, MAP_y*tile_size), "SFML works!");


    Clock main_time;


    const int level[] =
            {
                    0, 5, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                    5, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                    0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                    1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                    0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                    0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                    0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                    0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,

            };


    //array<string,WINDOW_SIZE_Y> minimap = {

    // create the tilemap from the level definition
    //TileMap map;
    //if (!map.load("E:\\final_project\\cpp_part\\images\\mapp.png", sf::Vector2u(32, 32), level, 16, 8))
    //return -1;




    std::vector <sf::RectangleShape> walls;
    walls.emplace_back(sf::Vector2f(WINDOW_SIZE_X, tile_size));
    walls.emplace_back(sf::Vector2f(WINDOW_SIZE_X, tile_size));
    walls.emplace_back(sf::Vector2f(tile_size, WINDOW_SIZE_Y));
    walls.emplace_back(sf::Vector2f(tile_size, WINDOW_SIZE_Y));
    // Устанавливаем позиции и цвета стенок
    walls[0].setPosition(0, 0); // Верхняя стенка
    walls[1].setPosition(0, WINDOW_SIZE_Y - tile_size); // Нижняя стенка
    walls[2].setPosition(0, 0); // Левая стенка
    walls[3].setPosition(WINDOW_SIZE_X - tile_size, 0); // Правая стенка

    for (auto &wall: walls) {
        wall.setFillColor(sf::Color::White);
    }




    /*Image player_image;
    player_image.loadFromFile("E:\\final_project\\cpp_part\\images\\chel.png");
    Texture player_texture;
    player_texture.loadFromImage(player_image);
    Sprite player_sprite;
    player_sprite.setTexture(player_texture);
    player_sprite.setTextureRect(IntRect(0, 0, 16,16));
    player_sprite.setPosition(50, 100);*/

    //int n=-45;
    //int direction = fmod(360 + fmod(n,360),360);
    //360/45 - 8 направлений
    sf::RectangleShape rectangle(sf::Vector2f(120.f, 50.f));
    Player p(WINDOW_SIZE_X / 2, WINDOW_SIZE_Y / 2, 16, 16);

    //float elapsed_time = main_time.getElapsedTime().asMilliseconds();


    new_map mapmap;
    //mapmap.makemap(level,18,8);

    while (window.isOpen()) {
        sf::Event event{};


        //float elapsed_time = main_time.getElapsedTime().asMicroseconds();
        //std::cout << elapsed_time << " === " << std::endl;
        main_time.restart(); //перезагружает время
        //elapsed_time = elapsed_time/800;

        while (window.pollEvent(event)) {
            // Кроме обычного способа наше окно будет закрываться по нажатию на Escape
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                window.close();
            /*
            if (event.type == sf::Event::MouseWheelScrolled)
            {
                if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
                    std::cout << "wheel type: vertical" << std::endl;
                else if (event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel)
                    std::cout << "wheel type: horizontal" << std::endl;
                else
                    std::cout << "wheel type: unknown" << std::endl;
                std::cout << "wheel movement: " << event.mouseWheelScroll.delta << std::endl;
                std::cout << "mouse x: " << event.mouseWheelScroll.x << std::endl;
                std::cout << "mouse y: " << event.mouseWheelScroll.y << std::endl;
            }
            if (event.type == sf::Event::MouseMoved)
            {
                std::cout << "new mouse x: " << event.mouseMove.x << std::endl;
                std::cout << "new mouse y: " << event.mouseMove.y << std::endl;
            }
            */

            if(event.type == sf::Event::KeyPressed){
                p.change_dir(event, main_time.getElapsedTime().asSeconds());
                p.go(event, main_time.getElapsedTime().asSeconds());
            }

        }
        //sf::Vector2f Position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        //cout << p.find_dir(p,event)<< endl;
        //p.move(speed,elapsed_time);
        //p.change_dir()

        /*if (Keyboard::isKeyPressed(Keyboard::A)){
            direction = 1;
            player_sprite.move(-speed*elapsed_time, 0);
            player_sprite.setTextureRect(IntRect(16*6, 0, 16,16));
        }
        if (Keyboard::isKeyPressed(Keyboard::D)){
            direction = 0;

            player_sprite.move(speed*elapsed_time, 0);
            player_sprite.setTextureRect(IntRect(16*2, 0, 16,16));

        }
        if (Keyboard::isKeyPressed(Keyboard::W)){
            direction = 3;

            player_sprite.move(0, -speed*elapsed_time);
            player_sprite.setTextureRect(IntRect(16*4, 0, 16,16));

        }
        if (Keyboard::isKeyPressed(Keyboard::S)){
            direction = 2;

            player_sprite.move(0, speed*elapsed_time);
            player_sprite.setTextureRect(IntRect(0, 0, 16,16));
        }*/
        //p.move_anim(elapsed_time);




        window.clear();
        /*collision(p,walls);


        for (const auto &wall: walls) {
            window.draw(wall);
        }*/




        /*auto d = mapmap.makemap(level,16,8);
        for(const auto &i: d)
            for(const auto &j: i)
                window.draw(j);
        */
        /*for (const auto &wall: mapmap.makemap(level,16,8)) {
            window.draw(wall);
        }*/
        //window.draw(map);
        //window.draw(mapmap);
        window.draw(p);
        Map_1::draw_Map_1(window,minimap);
        window.display();


    }


    return 0;
}



