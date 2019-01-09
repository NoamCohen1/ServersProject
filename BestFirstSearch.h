//
// Created by gal on 1/7/19.
//

#ifndef SERVERSPROJECT_BESTFIRSTSEARCH_H
#define SERVERSPROJECT_BESTFIRSTSEARCH_H

#include <queue>
#include "Searcher.h"
#include "State.h"

template<class T>
class BestFirstSearch : public Searcher<T> {
    class CompareStates {
        bool operator()(State<T>* first, State<T>* second) {
            return (first->getCost() > second->getCost());
        }
    };
public:
    virtual vector<State<T>*> search(Searchable<T> searchable) {
        // OPEN
        priority_queue<State<T> *, vector<State<T> *>, CompareStates> queueOpen;
        queueOpen.push(searchable.getInitialState());
        // CLOSED
        vector<State<T> *> statesClosed;
        vector<State<T> *> neighbors;

        while (!queueOpen.empty()) {
            State<T> *node = queueOpen.top();
            statesClosed.push_back(node);
            queueOpen.pop();
            if (node->equals(searchable.getGoalState())) {
                // update how many nodes the algorithm developed
                node->setHowManyNodes(statesClosed.size());
                // call func to return the path by the places
                // TODO
                vector<T> path;
                path.push_back(node);
                while (!(node->equals(searchable.getInitialState()))) {
                    node = node->getCameFrom();
                    path.push_back(node);
                }
                reverse(path.begin(), path.end());
                return path;
            } else {
                neighbors = searchable.getAllPossibleStates(node);
                for (State<T> *neighbor : neighbors) {
                    if (!(stateIsInOpen(neighbor, queueOpen)) && !(stateIsInClosed(neighbor, statesClosed))) {
                        // TODO - check if needed or done in getAllPossibleStates
                        neighbor->setCameFrom(node);
                        neighbor->setCost(neighbor->getCost() + node->getCost());
                        queueOpen.push(neighbor);
                    } else if (neighbor->getCost() >
                               (neighbor->getCost() - neighbor->getCameFrom().getCost() + node->getCost())) {
                        if (!(stateIsInOpen(neighbor))) {
                            for (State<T> *s : statesClosed) {
                                if (neighbor->equals(s)) {
                                    statesClosed.erase(remove(statesClosed.begin(), statesClosed.end(), s), statesClosed.end());
                                    queueOpen.push(neighbor);
                                }
                            }
                        } else {
                            neighbor->setCost(neighbor->getCost() - neighbor->getCameFrom().getCost() + node->getCost());
                            neighbor->setCameFrom(node);
                            queueOpen = updateQueueOpen(queueOpen);
                        }
                    }
                }
            }
        }
    }

    priority_queue<State<T>*> updateQueueOpen(priority_queue<State<T>*> &queueOpen) {
        priority_queue<State<T>*> result;
        while (!queueOpen.empty()) {
            State<T>* node = queueOpen.top();
            result.push(node);
            queueOpen.pop();
        }
        return result;
    }

    bool stateIsInOpen(State<T>* state, priority_queue<State<T>*> queueOpen) {
        while (!queueOpen.empty()) {
            if (state->equals(queueOpen.top())) {
                return true;
            }
            queueOpen.pop();
        }
        return false;
    }

    bool stateIsInClosed(State<T>* state, vector<State<T>*> statesClosed) {
        for (State<T>* s : statesClosed) {
            if (state->equals(s)) {
                return true;
            }
        }
        return false;
    }
};


#endif //SERVERSPROJECT_BESTFIRSTSEARCH_H
