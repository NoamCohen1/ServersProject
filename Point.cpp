#include "Point.h"

string Point::getPath(vector<State<Point> *> pathVector) {
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
    string finalPath = "";
    for (int k = 0; k < path.length(); ++k) {
        if (path[k] == 'R') {
            finalPath += "Right,";
        } else if (path[k] == 'L') {
            finalPath += "Left,";
        } else if (path[k] == 'U') {
            finalPath += "Up,";
        } else if (path[k] == 'D') {
            finalPath += "Down,";
        }
    }
    string st = finalPath.substr(0, finalPath.length() - 1);
    return st;
}