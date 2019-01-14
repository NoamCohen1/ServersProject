//
// Created by gal on 1/7/19.
//

#ifndef SERVERSPROJECT_BESTFIRSTSEARCH_H
#define SERVERSPROJECT_BESTFIRSTSEARCH_H

#include <queue>
#include "Searcher.h"
#include "State.h"
#include <iostream>

template<class T>
class BestFirstSearch : public Searcher<T> {
    class CompareStates {
    public:
        bool operator()(State<T> *first, State<T> *second) {
            return (first->getCost() > second->getCost());
        }
    };

public:
    virtual string search(Searchable<T> *searchable) {
        // OPEN
        priority_queue<State<T> *, vector<State<T> *>, CompareStates> queueOpen;
        queueOpen.push(searchable->getInitialState());
        // CLOSED
        vector<State<T> *> statesClosed;
        vector<State<T> *> neighbors;
        string solution = "";
        while (!queueOpen.empty()) {
            State<T> *node = queueOpen.top();
            // if the initial point is unreachable - does not have any neighbors
            if ((node->equals(searchable->getInitialState())) && (node->getCost() == (-1))) {
                solution = "-1";
                return solution;
            }
            statesClosed.push_back(node);
            queueOpen.pop();
            if (node->equals(searchable->getGoalState())) {
                // update how many nodes the algorithm developed
                node->setHowManyNodes(statesClosed.size());
                // call func to return the path by the places
                // TODO
                vector<State<T> *> path;
                path.push_back(node);
                //solution += to_string((int) node->getCost()) + "," + to_string(node->getHowManyNodes());
                while (!(node->equals(searchable->getInitialState()))) {
                    node = node->getCameFrom();
                    path.push_back(node);
                }
                solution = node->getState().getPath(path);
                return solution;
            } else {
                neighbors = searchable->getAllPossibleStates(node);
                for (State<T> *neighbor : neighbors) {
                    if (!(stateIsInOpen(neighbor, queueOpen)) && !(stateIsInClosed(neighbor, statesClosed))) {
                        neighbor->setCameFrom(node);
                        neighbor->setCost(neighbor->getCost() + node->getCost());
                        queueOpen.push(neighbor);
                    } else if ((neighbor->getCameFrom() != nullptr) && (neighbor->getCost() > (neighbor->getCost() - neighbor->getCameFrom()->getCost() + node->getCost()))) {
//                        if (!(stateIsInOpen(neighbor, queueOpen))) {
//                            for (State<T> *s : statesClosed) {
//                                if (neighbor->equals(s)) {
//                                    statesClosed.erase(s*/*remove(statesClosed.begin(), statesClosed.end(), s), statesClosed.end()*/);
//                                    queueOpen.push(neighbor);
//                                }
//                            }
                        if (stateIsInClosed(neighbor, statesClosed)) {
                            //cout << "oof" << endl;
                        } else {
                            neighbor->setCost(neighbor->getCost() - neighbor->getCameFrom()->getCost() + node->getCost());
                            neighbor->setCameFrom(node);
                            queueOpen = updateQueueOpen(queueOpen);
                        }
                    }
                }
            }
        }
        solution = "-1";
        return solution;
    }

    priority_queue<State<T> *, vector<State<T> *>, CompareStates>
    updateQueueOpen(priority_queue<State<T> *, vector<State<T> *>, CompareStates> &queueOpen) {
        priority_queue<State<T> *, vector<State<T> *>, CompareStates> result;
        while (!queueOpen.empty()) {
            State<T> *node = queueOpen.top();
            result.push(node);
            queueOpen.pop();
        }
        return result;
    }

    bool stateIsInOpen(State<T> *state, priority_queue<State<T> *, vector<State<T> *>, CompareStates> queueOpen) {
        while (!queueOpen.empty()) {
            if (state->equals(queueOpen.top())) {
                return true;
            }
            queueOpen.pop();
        }
        return false;
    }

    bool stateIsInClosed(State<T> *state, vector<State<T> *> statesClosed) {
        for (State<T> *s : statesClosed) {
            if (state->equals(s)) {
                return true;
            }
        }
        return false;
    }
};


#endif //SERVERSPROJECT_BESTFIRSTSEARCH_H
