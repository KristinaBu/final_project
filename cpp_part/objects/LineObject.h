
#ifndef CPP_PART_LINEOBJECT_H
#define CPP_PART_LINEOBJECT_H


#include "Objects.h"
#include "Point.h"

class LineObject : public Object {
protected:
    float x1, y1;
    float x2, y2;
    Image image;
    Texture texture;
    Sprite sprite;
public:
    LineObject(float x1_, float y1_, float x2_, float y2_) : Object() {
        x1 = x1_;
        y1 = y1_;
        x2 = x2_;
        y2 = y2_;
    }

    LineObject() : Object() {
        x1 = 0;
        y1 = 0;
        x2 = 0;
        y2 = 0;
    }

    static Point *intersection(double x1_, double y1_, double x2_, double y2_,
                               double x3_, double y3_, double x4_, double y4_) {
        //начало первой линии, конец второй линии, начало второй линии, конец первой линии
        double d = (y4_ - y3_) * (x2_ - x1_) - (x4_ - x3_) * (y2_ - y1_);
        if (d == 0.0) return nullptr; //линии параллельны

        double ua = ((x4_ - x3_) * (y1_ - y3_) - (y4_ - y3_) * (x1_ - x3_)) / d;
        double ub = ((x2_ - x1_) * (y1_ - y3_) - (y2_ - y1_) * (x1_ - x3_)) / d;
        if (ua >= 0.0 && ua <= 1.0 && ub >= 0.0 && ub <= 1.0) {
            //точка пересечения
            return new Point(x1_ + ua * (x2_ - x1_), y1_ + ua * (y2_ - y1_));
        }
        return nullptr;
    }

};


#endif //CPP_PART_LINEOBJECT_H
