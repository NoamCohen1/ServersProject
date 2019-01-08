//
// Created by gal on 1/8/19.
//

#ifndef SERVERSPROJECT_STATE_H
#define SERVERSPROJECT_STATE_H

template<class T>
class State {
    T* state;
    double cost;
    State<T> *cameFrom;
public:
    State(T* state, double cost) {
        this->state = state;
        this->cost = cost;
        this->cameFrom = nullptr;
    }

    bool equals(State<T>* s) {
        return (this->state == s->state);
    }

    void setCameFrom(State<T>* s) {
        this->cameFrom = s;
    }

    State<T>* getCameFrom() {
        return this->cameFrom;
    }

    void setCost(double newCost) {
        this->cost = newCost;
    }

    double getCost() {
        return this->cost;
    }
};


#endif //SERVERSPROJECT_STATE_H
