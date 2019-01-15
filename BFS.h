#ifndef SERVERSPROJECT_BFS_H
#define SERVERSPROJECT_BFS_H

#include <queue>
#include "Searcher.h"
#include "State.h"

template<class T>
class BFS : public Searcher<T> {
public:
    virtual string search(Searchable<T> *searchable) {
        string solution = "";
        string solutionToFile = "";
        int howManyNodes = 0;
        double finalCost = 0;
        vector<State<T>*> visited;
        // Create a queue for BFS
        queue<State<T>*> statesQueue;
        vector<State<T>*> neighbors;

        if (searchable->getInitialState()->getCost() == (-1)) {
            solution = "-1";
            solutionToFile = "-1,0";
            //searchable->writeCostAndNodes(solutionToFile);
            return solution;
        }

        // Mark the current node as visited and enqueue it
        visited.push_back(searchable->getInitialState());
        statesQueue.push(searchable->getInitialState());

        while(!statesQueue.empty()) {
            // Dequeue a vertex from queue
            State<T>* node = statesQueue.front();
            statesQueue.pop();
            ++howManyNodes;
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
                //searchable->writeCostAndNodes(solutionToFile);
                return solution;
            }
            neighbors = searchable->getAllPossibleStates(node);
            // Get all adjacent vertices of the dequeued
            // vertex s. If a adjacent has not been visited,
            // then mark it visited and enqueue it
            for (State<T>* neighbor : neighbors) {
                if (!stateIsInVisited(neighbor, visited)) {
                    neighbor->setCameFrom(node);
                    visited.push_back(neighbor);
                    statesQueue.push(neighbor);
                }
            }
        }
        solution = "-1";
        solutionToFile += "-1," + to_string(howManyNodes);
        //searchable->writeCostAndNodes(solutionToFile);
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

#endif //SERVERSPROJECT_BFS_H
