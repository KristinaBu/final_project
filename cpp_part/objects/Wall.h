#ifndef CPP_PART_WALL_H
#define CPP_PART_WALL_H

#include "LineObject.h"

class Wall : public LineObject {
public:
    Wall() {
        this->x1 = 0;
        this->y1 = 0;
        this->x2 = 0;
        this->y2 = 0;
        this->set_type(WallType);
    }

    Wall(float x1_, float y1_, float x2_, float y2_) {
        if(x1_ <= x2_){
            this->x1 = x1_;
            this->x2 = x2_;
        }
        else{
            this->x1 = x2_;
            this->x2 = x1_;
        }
        if(y1_ <= y2_){
            this->y1 = y1_;
            this->y2 = y2_;
        }
        else{
            this->y1 = y2_;
            this->y2 = y1_;
        }
        this->y1 = y1_;
        this->y2 = y2_;
        this->set_type(WallType);
    }

    float get_x1() { return this->x1; }

    float get_y1() { return this->y1; }

    float get_x2() { return this->x2; }

    float get_y2() { return this->y2; }

};


#endif //CPP_PART_WALL_H
