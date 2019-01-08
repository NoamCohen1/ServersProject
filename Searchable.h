//
// Created by gal on 1/7/19.
//

#ifndef SERVERSPROJECT_SEARCHABLE_H
#define SERVERSPROJECT_SEARCHABLE_H

#include <vector>
#include "State.h"

using namespace std;

template <class Solu>
class Searchable {
public:
    virtual State<Solu> getInitialState() = 0;

    virtual State<Solu> getGoalState() = 0;

    virtual vector<State<Solu>> getAllPossibleStates(State<Solu> state) = 0;
};
#endif //SERVERSPROJECT_SEARCHABLE_H
