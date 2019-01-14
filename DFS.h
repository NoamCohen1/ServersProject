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
        string solutionToFile = "";
        int howManyNodes = 0;
        double finalCost = 0;
        vector<State<T>*> visited;
        // Create a queue for BFS
        stack<State<T>*> statesStack;
        vector<State<T>*> neighbors;

        if (searchable->getInitialState()->getCost() == (-1)) {
            solution = "-1";
            solutionToFile = "-1";
            searchable->writeCostAndNodes(solutionToFile);
            return solution;
        }

        // Mark the current node as visited and enqueue it
        statesStack.push(searchable->getInitialState());

        while(!statesStack.empty()) {
            // Dequeue a vertex from queue
            State<T>* node = statesStack.top();
            statesStack.pop();
            ++howManyNodes;
            if (!stateIsInVisited(node, visited)) {
                visited.push_back(node);
            }
            if (node->equals(searchable->getGoalState())) {
                vector<State<T> *> path;
                path.push_back(node);
                finalCost += node->getCost();
                while (!(node->equals(searchable->getInitialState()))) {
                    node = node->getCameFrom();
                    finalCost += node->getCost();
                    path.push_back(node);
                }
                solution = node->getState().getPath(path);
                solutionToFile += to_string((int) finalCost) + "," + to_string(howManyNodes);
                searchable->writeCostAndNodes(solutionToFile);
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
        solutionToFile = "-1";
        searchable->writeCostAndNodes(solutionToFile);
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
