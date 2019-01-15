#ifndef SERVERSPROJECT_POINT_H
#define SERVERSPROJECT_POINT_H

#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include "State.h"

using namespace std;

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

    string getPath(vector<State<Point>*> pathVector);
};

#endif //SERVERSPROJECT_POINT_H
