//
// Created by Karamel on 18.02.2023.
//
#include <iostream>
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "map.h"
#include "objects/Objects.h"
#include "Player.h"
#include <cmath>

#include "global_const.h"

using namespace sf;
using namespace std;


int main() {

    //сглаживание неровных и диагональных линий
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_X * 3, WINDOW_SIZE_Y * 3), "SFML works!");

    Clock main_time;

    sf::RectangleShape rectangle(sf::Vector2f(120.f, 50.f));
    Player p(WINDOW_SIZE_X / 2, WINDOW_SIZE_Y / 2);
    //длина 15 высота 10
    /*{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},,*/
    /*{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                                         {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                         {1,0,0,1,0,0,0,0,1,0,0,0,0,0,1},
                                         {1,0,0,1,0,0,0,0,1,0,0,0,0,0,1},
                                         {1,0,0,1,0,0,0,0,1,0,0,0,0,0,1},
                                         {1,0,0,1,0,0,0,0,1,0,0,0,0,0,1},
                                         {1,0,0,1,0,0,0,0,1,0,0,0,0,0,1},
                                         {1,0,0,1,0,0,0,0,1,0,0,0,0,0,1},
                                         {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},*/

    Map map1(vector<vector<int>>({
                                         {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                                         {1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
                                         {1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
                                         {1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
                                         {1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
                                         {1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
                                         {1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
                                         {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                                 }));
    CircleShape c; // drawing centerpoint
    c.setRadius(2);
    c.setFillColor(Color::Red);

    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
    std::vector<Object> objects_in_game;

    window.setKeyRepeatEnabled(false);

    while (window.isOpen()) {
        sf::Event event{};
        window.clear();
        //направление взгляда
        sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(p.get_x(), p.get_y())),
                sf::Vertex(sf::Vector2f(p.get_x() + 1000 * cos(p.get_direction()),
                                        p.get_y() + 1000 * sin(p.get_direction())))
        };
        // ты сосиска бебебе
        sf::Vertex line_left[] = {
                sf::Vertex(sf::Vector2f(p.get_x(), p.get_y())),
                sf::Vertex(sf::Vector2f(p.get_x() + 1000 * cos(p.get_direction() - PI / 4),
                                        p.get_y() + 1000 * sin(p.get_direction() - PI / 4)))
        };
        sf::Vertex line_right[] = {
                sf::Vertex(sf::Vector2f(p.get_x(), p.get_y())),
                sf::Vertex(sf::Vector2f(p.get_x() + 1000 * cos(p.get_direction() + PI / 4),
                                        p.get_y() + 1000 * sin(p.get_direction() + PI / 4)))
        };


        while (window.pollEvent(event)) {

            // Кроме обычного способа наше окно будет закрываться по нажатию на Escape
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                p.set_key(event.key.code, true);

            }
            if (event.type == sf::Event::KeyReleased) {
                p.set_key(event.key.code, false);

            }
        }
        // ты козявочник
        map1.draw(window);
        p.go(main_time.getElapsedTime().asSeconds(), map1.get_objects_in_game());
        window.draw(p.getSprite());
        c.setPosition(p.getSprite().getPosition());
        window.draw(c);

        window.draw(line, 2, sf::Lines);
        window.draw(line_left, 2, sf::Lines);
        window.draw(line_right, 2, sf::Lines);

        window.display();
        main_time.restart(); //перезагружает время
    }


    return 0;
}



