//
// Created by noam on 1/10/19.
//

#ifndef SERVERSPROJECT_DFS_H
#define SERVERSPROJECT_DFS_H

#include <stack>
#include "Searcher.h"
#include "State.h"

template<class T>
class DFS : public Searcher<T> {
public:
    virtual string search(Searchable<T> *searchable) {
        string solution = "";
        vector<State<T>*> visited;
        // Create a queue for BFS
        stack<State<T>*> statesStack;
        vector<State<T>*> neighbors;

        if (searchable->getInitialState()->getCost() == (-1)) {
            solution = "-1";
            return solution;
        }

        // Mark the current node as visited and enqueue it
        statesStack.push(searchable->getInitialState());

        while(!statesStack.empty()) {
            // Dequeue a vertex from queue
            State<T>* node = statesStack.top();
            //cout << s << " ";
            statesStack.pop();
            if (!stateIsInVisited(node, visited)) {
                visited.push_back(node);
            }
            if (node->equals(searchable->getGoalState())) {
                vector<State<T> *> path;
                path.push_back(node);
                //solution += to_string((int) node->getCost()) + "," + to_string(node->getHowManyNodes());
                while (!(node->equals(searchable->getInitialState()))) {
                    node = node->getCameFrom();
                    path.push_back(node);
                }
                solution = node->getState().getPath(path);
                return solution;
            }
            neighbors = searchable->getAllPossibleStates(node);
            // Get all adjacent vertices of the dequeued
            // vertex s. If a adjacent has not been visited,
            // then mark it visited and enqueue it
            for (State<T>* neighbor : neighbors) {
                if (!stateIsInVisited(neighbor, visited)) {
                    neighbor->setCameFrom(node);
                    statesStack.push(neighbor);
                }
            }
        }
        solution = "-1";
        return solution;
    }

    bool stateIsInVisited(State<T> *state, vector<State<T> *> visited) {
        for (State<T> *s : visited) {
            if (state->equals(s)) {
                return true;
            }
        }
        return false;
    }
};


#endif //SERVERSPROJECT_DFS_H
