#ifndef CPP_PART_OBJECTS_H
#define CPP_PART_OBJECTS_H
#include "math.h"
#include "global_const.h"
#include "iostream"

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

enum Types{
    Wall_, Enemy_, PickUp_
};

class Object{
private:
    Types type;
    //координаты

    float x1, y1;
    float x2, y2;
    //for type = Wall
public:
    Object(){}
    void set_type(Types type){
        this->type = type;
    }
    Types get_type(){
        return this->type;
    }

    //for obj.type = Wall
    float get_x1(){ return this->x1; }
    float get_y1(){ return this->y1; }
    float get_x2(){ return this->x2; }
    float get_y2(){ return this->y2; }
    void set(float x1_, float y1_, float x2_, float y2_, Types type){
        this->x1 = x1_; this->y1 = y1_; this->x2 = x2_; this->y2 = y2_;
        this->type = type;
    }
};


#endif //CPP_PART_OBJECTS_H
