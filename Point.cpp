//
// Created by noam on 1/8/19.
//

#include "Point.h"

string Point::getPath(vector<State<Point>*> pathVector) {
    string path = "";
    for (int i = 0; i < (pathVector.size() - 1); ++i) {
        int i1 = pathVector[i]->getState().getI();
        int j1 = pathVector[i]->getState().getJ();
        int i2 = pathVector[i + 1]->getState().getI();
        int j2 = pathVector[i + 1]->getState().getJ();
        if ((i1 == i2) && (j1 == (j2 + 1))) {
            path += "R";
        } else if ((i1 == i2) && (j1 == (j2 - 1))) {
            path += "L";
        } else if ((i1 == (i2 + 1)) && (j1 == j2)) {
            path += "D";
        } else if ((i1 == (i2 - 1)) && (j1 == j2)) {
            path += "U";
        }
    }
    reverse(path.begin(), path.end());
    return path;
}