//
// Created by gal on 1/8/19.
//

#ifndef SERVERSPROJECT_STATE_H
#define SERVERSPROJECT_STATE_H

template <class T>
class State {
    T state;
    double cost;
    State<T> cameFrom;
public:
    State(T state) {
        this->state = state;
    }

    bool equals(State<T> s) {
        return state.equals(s.state);
    }
};


#endif //SERVERSPROJECT_STATE_H
