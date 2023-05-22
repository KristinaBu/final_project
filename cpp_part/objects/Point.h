#ifndef CPP_PART_POINT_H
#define CPP_PART_POINT_H

class Point {
private:
    double x;
    double y;
public:
    Point(double x, double y) {
        this->x = x;
        this->y = y;
    }

    double get_x() { return this->x; }

    double get_y() { return this->y; }

    bool operator==(Point p) {
        if (this->x == p.x && this->y == p.y) return true;
        return false;
    }

    bool operator!=(Point p) {
        if (*this == p) return false;
        return true;
    }
};

#endif //CPP_PART_POINT_H
