//
// Created by noam on 1/8/19.
//

#ifndef SERVERSPROJECT_POINT_H
#define SERVERSPROJECT_POINT_H

class Point {
    int i;
    int j;
public:
    Point(int i, int j) {
        this->i = i;
        this->j = j;
    }

    Point* getPoint() {
        return this;
    }

    int getI() {
        return this->i;
    }

    int getJ() {
        return this->j;
    }

    bool operator==(Point point) {
        return ((this->i == point.getI()) && (this->j == point.getJ()));
    }

    void setPoint(int i, int j) {
        this->i = i;
        this->j = j;
    }
};

#endif //SERVERSPROJECT_POINT_H
