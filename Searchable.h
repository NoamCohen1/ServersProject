//
// Created by gal on 1/7/19.
//

#ifndef SERVERSPROJECT_SEARCHABLE_H
#define SERVERSPROJECT_SEARCHABLE_H

#include <vector>
#include "State.h"

using namespace std;

template <class T>
class Searchable {
protected:
    vector<State<T>*> searchable;
    State<T>* initialState;
    State<T>* goalState;
public:
    Searchable(vector<State<T>*> searchable, State<T>* initialState, State<T>* goalState) {
        this->searchable = searchable;
        this->initialState = initialState;
        this->goalState = goalState;
    }

    const vector<State<T> *> &getSearchable() const {
        return this->searchable;
    }

    virtual State<T>* getInitialState() = 0;

    virtual State<T>* getGoalState() = 0;

    virtual vector<State<T>*> getAllPossibleStates(State<T>* state) = 0;
};
#endif //SERVERSPROJECT_SEARCHABLE_H
