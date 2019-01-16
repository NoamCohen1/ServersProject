#ifndef SERVERSPROJECT_ASTAR_H
#define SERVERSPROJECT_ASTAR_H

#include <queue>
#include "Searcher.h"
#include "State.h"
#include "MyClientHandler.h"
#include<bits/stdc++.h>

using namespace std;

template<class T>
class AStar : public Searcher<T> {
    class CompareStates {
    public:
        bool operator()(State<T> *first, State<T> *second) {
            return (first->getFgh() > second->getFgh());
        }
    };

public:
    virtual string search(Searchable<T> *searchable) {
        // OPEN
        priority_queue<State<T> *, vector<State<T> *>, CompareStates> queueOpen;
        searchable->getInitialState()->setFgh(0);
        queueOpen.push(searchable->getInitialState());
        // CLOSED
        vector<State<T> *> statesClosed;
        vector<State<T> *> neighbors;
        string solution = "";
        string solutionToFile = "";
        while (!queueOpen.empty()) {
            State<T> *node = queueOpen.top();
            // if the initial point is unreachable - does not have any neighbors
            if ((node->equals(searchable->getInitialState())) && (node->getCost() == (-1))) {
                solution = "-1";
                solutionToFile += "-1,0";
                //searchable->writeCostAndNodes(solutionToFile);
                return solution;
            }
            statesClosed.push_back(node);
            queueOpen.pop();
            if (node->equals(searchable->getGoalState())) {
                // update how many nodes the algorithm developed
                node->setHowManyNodes(statesClosed.size());
                vector<State<T> *> path;
                path.push_back(node);
                solutionToFile += to_string((int) node->getCost()) + "," + to_string(statesClosed.size());
                //searchable->writeCostAndNodes(solutionToFile);
                while (!(node->equals(searchable->getInitialState()))) {
                    node = node->getCameFrom();
                    path.push_back(node);
                }
                // call func to return the path by the places
                solution = node->getState().getPath(path);
                cout << "gallIsTheBesttt1111" << endl;
                return solution;
            } else {
                neighbors = searchable->getAllPossibleStates(node);
                for (State<T> *neighbor : neighbors) {
                    if (!(stateIsInOpen(neighbor, queueOpen)) && !(stateIsInClosed(neighbor, statesClosed))) {
                        neighbor->setCameFrom(node);
                        neighbor->setCost(neighbor->getCost() + node->getCost());
                        neighbor->setFgh(calculateFgh(neighbor, searchable->getGoalState()));
                        queueOpen.push(neighbor);
                    } else if ((neighbor->getCameFrom() != nullptr) && (neighbor->getCost() > (neighbor->getCost() -
                                                                                               neighbor->getCameFrom()->getCost() +
                                                                                               node->getCost()))) {
                        if (stateIsInClosed(neighbor, statesClosed)) {
                            continue;
                        } else {
                            neighbor->setCost(
                                    neighbor->getCost() - neighbor->getCameFrom()->getCost() + node->getCost());
                            neighbor->setFgh(calculateFgh(neighbor, searchable->getGoalState()));
                            neighbor->setCameFrom(node);
                            queueOpen = updateQueueOpen(queueOpen);
                        }
                    }
                }
            }
        }
        solution = "-1";
        solutionToFile += "-1," + to_string(statesClosed.size());
        //searchable->writeCostAndNodes(solutionToFile);
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

    double calculateFgh(State<T> *state, State<T> *goal) {
        // according to manhattan distance
        double f = 0;
        double h = abs(state->getState().getI() - goal->getState().getI()) +
                   abs(state->getState().getJ() - goal->getState().getJ());
        double g = state->getCost();
        f = g + h;
        return f;
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

#endif //SERVERSPROJECT_ASTAR_H
