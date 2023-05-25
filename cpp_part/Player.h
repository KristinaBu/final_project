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
    float direction = 0;
    float rotate_speed = PLAYER_ROTATE_SPEED;
    //вектор нажатых кнопок
    std::map<sf::Keyboard::Key, bool> key_state;
    Image image_wall;
    //прекомпиляция видимых стен
    vector<Texture> precompiledWallTexture;


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
        //данная формуза делает возможным загрузку изображения любого размера
        p_sprite.setScale((float) tile_size / (float) p_texture.getSize().x,
                          (float) tile_size / (float) p_texture.getSize().y);

        this->p_sprite.setOrigin((float) p_texture.getSize().x / 2, (float) p_texture.getSize().y / 2);
        this->p_sprite.setPosition(x, y);

        key_state[sf::Keyboard::W] = false;
        key_state[sf::Keyboard::A] = false;
        key_state[sf::Keyboard::S] = false;
        key_state[sf::Keyboard::D] = false;
        image_wall.loadFromFile(R"(assets\Marble.png)");

        //заранее загружаем в текстуру стены изображение
        for (int i = 0; i < image_wall.getSize().x; i++){
            Texture t;
            t.loadFromImage(image_wall, sf::IntRect(i, 0, pixelResolution, image_wall.getSize().y));
            precompiledWallTexture.push_back(t);
        }
    }

    Sprite getSprite() {
        return p_sprite;
    }

    void set_key(sf::Keyboard::Key b, bool pressed) {
        this->key_state[b] = pressed;
    }

    double get_direction() const { return this->direction; }

    //движение
    void go(double d_time, const std::vector<Object *> &objects_in_game) {

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
    //коллизия
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
    //2д карта
    void draw_minimap(sf::RenderWindow &i_window, Map map){
        CircleShape c; // игрок
        c.setRadius(4);
        c.setFillColor(Color::Red);
        c.setOrigin(4, 4);
        c.setPosition(x, y);
        i_window.draw(c);
        //райкастинг
        int pixelCounter = -1;
        for(
                float angle = direction - PLAYER_FOV / 2;
                angle <= direction + PLAYER_FOV / 2;
                angle += PLAYER_FOV / (float)WINDOW_SIZE_X * pixelResolution ){

            pixelCounter+=pixelResolution;
            // Ищем ближайшую для рендера стену
            Wall* contextObj = nullptr;
            //течка пересечения
            Point* intersect = nullptr;
            //полученная точка пересечения
            Point* contextIntersect = nullptr;
            float dist = 1000000000.0;
            for (Object* obj: map.get_objects_in_game()){
                if (obj->get_type() != WallType) continue;
                Wall* wall = reinterpret_cast<Wall *>(obj);
                intersect = Wall::intersection(x, y, x + 100000 * cos(angle), y + 100000 * sin(angle),
                                               wall->get_x1(), wall->get_y1(), wall->get_x2(), wall->get_y2());
                if (intersect != nullptr && sqrt(pow(x - intersect->get_x(), 2) + pow(y - intersect->get_y(), 2)) < dist){
                    dist = sqrt(pow(x - intersect->get_x(), 2) + pow(y - intersect->get_y(), 2));
                    contextObj = wall;
                    contextIntersect = intersect;
                }
            }
            //расстояние от игрока до пересечения взгляда и стены
            dist *= cos(direction-angle);
            int h = min((int) (PLAYER_FOV * WINDOW_SIZE_X / dist), (int) WINDOW_SIZE_Y/2);
            sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(pixelCounter, WINDOW_SIZE_Y/2-h), Color::Blue),//Color(dist > FOG_LEVEL ? FOG_LEVEL / dist : 1, dist > FOG_LEVEL ? FOG_LEVEL / dist : 1, dist > FOG_LEVEL ? FOG_LEVEL / dist : 1, 1)),
                    sf::Vertex(sf::Vector2f(pixelCounter, WINDOW_SIZE_Y/2+h), Color::Blue) //Color(dist > FOG_LEVEL ? FOG_LEVEL / dist : 1, dist > FOG_LEVEL ? FOG_LEVEL / dist : 1, dist > FOG_LEVEL ? FOG_LEVEL / dist : 1, 1))
            };
            sf::Vertex shadowline[] = {
                    sf::Vertex(sf::Vector2f(pixelCounter, WINDOW_SIZE_Y/2-h), Color((dist > FOG_LEVEL ? FOG_LEVEL / dist : 1) * 255, (dist > FOG_LEVEL ? FOG_LEVEL / dist : 1) * 255, (dist > FOG_LEVEL ? FOG_LEVEL / dist : 1) * 255, 255)),
                    sf::Vertex(sf::Vector2f(pixelCounter, WINDOW_SIZE_Y/2+h), Color((dist > FOG_LEVEL ? FOG_LEVEL / dist : 1) * 255, (dist > FOG_LEVEL ? FOG_LEVEL / dist : 1) * 255, (dist > FOG_LEVEL ? FOG_LEVEL / dist : 1) * 255, 255))
            };
            sf::Vertex minimapLine[] = {
                    sf::Vertex(sf::Vector2f(x, y), Color::Green),
                    sf::Vertex(sf::Vector2f(contextIntersect->get_x(), contextIntersect->get_y()), Color::Blue)
            };
            i_window.draw(line, 2, sf::Lines);
            i_window.draw(shadowline, 2, sf::Lines);
            i_window.draw(minimapLine, 2, sf::Lines);
        }

    }

    float func_dict(float x, float y, float xx, float yy){
        return  sqrt(pow(x - xx,2) + pow(y - yy, 2));
    }

    void draw_texture_(sf::RenderWindow &i_window, Map map){
        Texture texture_line;
        Sprite line_sprite;

        CircleShape c;
        c.setRadius(4);
        c.setFillColor(Color::Red);
        c.setOrigin(4, 4);
        c.setPosition(x, y);
        i_window.draw(c);

        int pixelCounter = -1;
        for(
                float angle = direction - PLAYER_FOV / 2;
                angle <= direction + PLAYER_FOV / 2;
                angle += PLAYER_FOV / (float)WINDOW_SIZE_X * pixelResolution ){

            pixelCounter+=pixelResolution;
            // Ищем ближайшую для рендера стену
            Wall* contextObj = nullptr;
            //течка пересечения
            Point* intersect = nullptr;
            //полученная точка пересечения
            Point* contextIntersect = nullptr;
            //коэффиценит пропорциональности отрезка стены с самой стеной
            float proportion_intersection = 0;
            //точка пересечения взгляда и стены, пропорционально отложенная на координату Х изображения
            float proportion_texture_x = 0;

            float dist = 1000000000.0;
            for (Object* obj: map.get_objects_in_game()){
                if (obj->get_type() != WallType) continue;
                Wall* wall = reinterpret_cast<Wall *>(obj);
                intersect = Wall::intersection(x, y, x + 100000 * cos(angle), y + 100000 * sin(angle),
                                               wall->get_x1(), wall->get_y1(), wall->get_x2(), wall->get_y2());
                if (intersect != nullptr && sqrt(pow(x - intersect->get_x(), 2) + pow(y - intersect->get_y(), 2)) < dist){
                    dist = sqrt(pow(x - intersect->get_x(), 2) + pow(y - intersect->get_y(), 2));
                    contextObj = wall;
                    contextIntersect = intersect;
                }
            }

            dist *= cos(direction-angle);
            int h = min((int) (PLAYER_FOV * WINDOW_SIZE_X / dist), (int) WINDOW_SIZE_Y/2);
            proportion_intersection = func_dict(contextObj->get_x1(), contextObj->get_y1(), contextIntersect->get_x(), contextIntersect->get_y())
                                      / func_dict(contextObj->get_x1(), contextObj->get_y1(), contextObj->get_x2(),  contextObj->get_y2());
            proportion_texture_x = image_wall.getSize().x * proportion_intersection;
            //прекомпиляция - заранее загрузить текстуру в вектор и уже потом выкладывать на экран
            line_sprite.setTexture(precompiledWallTexture.at(proportion_texture_x-1));
            line_sprite.setScale(1, 4*h / (float) p_texture.getSize().y);
            line_sprite.setOrigin((float) precompiledWallTexture.at(proportion_texture_x-1).getSize().x / 2, (float) precompiledWallTexture.at(proportion_texture_x-1).getSize().y / 2);
            line_sprite.setPosition(pixelCounter,WINDOW_SIZE_Y/2);


            sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(pixelCounter, WINDOW_SIZE_Y/2-h), Color::Blue),//Color(dist > FOG_LEVEL ? FOG_LEVEL / dist : 1, dist > FOG_LEVEL ? FOG_LEVEL / dist : 1, dist > FOG_LEVEL ? FOG_LEVEL / dist : 1, 1)),
                    sf::Vertex(sf::Vector2f(pixelCounter, WINDOW_SIZE_Y/2+h), Color::Blue) //Color(dist > FOG_LEVEL ? FOG_LEVEL / dist : 1, dist > FOG_LEVEL ? FOG_LEVEL / dist : 1, dist > FOG_LEVEL ? FOG_LEVEL / dist : 1, 1))
            };
            sf::Vertex shadowline[] = {
                    sf::Vertex(sf::Vector2f(pixelCounter, WINDOW_SIZE_Y/2-h), Color(1,1,1, (dist > FOG_LEVEL ? 1 - FOG_LEVEL / dist : 0) * 255)),
                    sf::Vertex(sf::Vector2f(pixelCounter, WINDOW_SIZE_Y/2+h), Color(1,1,1, (dist > FOG_LEVEL ? 1 - FOG_LEVEL / dist : 0) * 255))
            };
            sf::Vertex minimapLine[] = {
                    sf::Vertex(sf::Vector2f(x, y), Color::Green),
                    sf::Vertex(sf::Vector2f(contextIntersect->get_x(), contextIntersect->get_y()), Color::Blue)
            };

            i_window.draw(line, 2, sf::Lines);
            i_window.draw(line_sprite);
            i_window.draw(shadowline, 2, sf::Lines);
            i_window.draw(minimapLine, 2, sf::Lines);
        }

    }
};

#endif //CPP_PART_PLAYER_H
