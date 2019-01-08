//
// Created by gal on 1/7/19.
//

#include "BestFirstSearch.h"

//template <class T>
//vector<T> BestFirstSearch::search(Searchable<T> searchable) {
//    // OPEN
//    priority_queue<int> queueOpen;
//    queueOpen.push(searchable.getInitialState());
//    // CLOSED
//    vector<State<T>> statesClosed;
//    while (!queueOpen.empty()) {
//        State<T> node = queueOpen.top();
//        statesClosed.push_back(node);
//        queueOpen.pop();
//        if (node.equals(searchable.getGoalState())) {
//            // call func to return the path by the places
//        }
//        vector<State<T>> neighbors;
//        neighbors = searchable.getAllPossibleStates(node);
//        for (auto neighbor : neighbors) {
//            if (!(stateIsInOpen(neighbor, queueOpen)) && !(stateIsInClosed(neighbor, statesClosed))) {
//                neighbor.setCameFrom(node);
//            }
//        }
//    }
//}