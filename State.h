#ifndef SERVERSPROJECT_STATE_H
#define SERVERSPROJECT_STATE_H

template<class T>
class State {
    T state;
    double cost;
    State<T> *cameFrom;
    int howManyNodes;
    double fgh;
public:
    State(T state, double cost) : state(state), cost(cost) {
        this->cameFrom = nullptr;
        this->howManyNodes = 0;
    }

    bool equals(State<T> *s) {
        return (this->state == s->state);
    }

    void setCameFrom(State<T> *s) {
        this->cameFrom = s;
    }

    State<T> *getCameFrom() {
        return this->cameFrom;
    }

    void setCost(double newCost) {
        this->cost = newCost;
    }

    double getCost() {
        return this->cost;
    }

    T getState() {
        return this->state;
    }

    void setHowManyNodes(int nodes) {
        this->howManyNodes = nodes;
    }

    int getHowManyNodes() {
        return this->howManyNodes;
    }

    void setFgh(double fgh) {
        this->fgh = fgh;
    }

    double getFgh() {
        return this->fgh;
    }
};

#endif //SERVERSPROJECT_STATE_H
