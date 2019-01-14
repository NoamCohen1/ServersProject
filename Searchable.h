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
    vector<pair<double, pair<int, int>>> pairsVector;
    pair<double, pair<int, int>> initialPair;
    pair<double, pair<int, int>> goalPair;
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

    vector<pair<double, pair<int, int>>> getPairsVector() {
        return this->pairsVector;
    }

    pair<double, pair<int, int>> getInitialPair() {
        return this->initialPair;
    }

    pair<double, pair<int, int>> getGoalPair() {
        return this->goalPair;
    }

    void setPairsVector(vector<pair<double, pair<int, int>>> pairsVector) {
        this->pairsVector = pairsVector;
    }

    void setInitialPair(pair<double, pair<int, int>> initialPair) {
        this->initialPair = initialPair;
    }

    void setGoalPair(pair<double, pair<int, int>> goalPair) {
        this->goalPair = goalPair;
    }

    //virtual void writeCostAndNodes();
};
#endif //SERVERSPROJECT_SEARCHABLE_H
