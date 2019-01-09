//
// Created by gal on 1/9/19.
//

#include "Matrix.h"

vector<State<Point>*> Matrix::getAllPossibleStates(State<Point>* state) {
    vector<State<Point>*> neighbors;
    int i = state->getState().getI();
    int j = state->getState().getJ();
    for (int k = 0; k < this->searchable.size(); ++k) {
        int k1 = this->searchable[k]->getState().getI();
        int k2 = this->searchable[k]->getState().getJ();
        if (((k1 == (i - 1)) && (k2 == j)) || ((k1 == (i + 1)) && (k2 == j))
        || ((k1 == i) && (k2 == (j - 1))) || ((k1 == i) && (k2 == (j + 1)))) {
            if (this->searchable[k]->getCost() != (-1)) {
                neighbors.push_back(this->searchable[k]);
            }
        }
    }
    return neighbors;
}

State<Point>* Matrix::getGoalState() {
    return this->goalState;
}

State<Point>* Matrix::getInitialState() {
    return this->initialState;
}