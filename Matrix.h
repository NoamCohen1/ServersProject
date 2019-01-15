#ifndef SERVERSPROJECT_MATRIX_H
#define SERVERSPROJECT_MATRIX_H

#include <fstream>
#include <vector>
#include "Searchable.h"
#include "Point.h"

class Matrix : public Searchable<class Point> {
public:
    Matrix(vector<State<Point> *> searchable, State<Point> *initialState, State<Point> *goalState) :
            Searchable(searchable, initialState, goalState) {}

    virtual State<Point> *getInitialState();

    virtual State<Point> *getGoalState();

    virtual vector<State<Point> *> getAllPossibleStates(State<Point> *state);

    virtual void writeCostAndNodes(string solution);
};


#endif //SERVERSPROJECT_MATRIX_H
