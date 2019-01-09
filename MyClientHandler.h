//
// Created by gal on 1/9/19.
//

#ifndef SERVERSPROJECT_MYCLIENTHANDLER_H
#define SERVERSPROJECT_MYCLIENTHANDLER_H

#include "ClientHandler.h"
#define START_STRING 0
#define DELIMITER ","

class MyClientHandler : public ClientHandler {
    Solver<Searchable<Point>*, string>* solver;
    CacheManager* cacheManager;
public:
    MyClientHandler(Solver<Searchable<Point>*, string>* solver, CacheManager* cacheManager) {
        this->solver = solver;
        this->cacheManager = cacheManager;
    }

    virtual void handleClient(int sockfd);

    vector<string> split(string buffer);

    State<Point>* getInitialState(vector<State<Point>*> searchable, Point initial);

    State<Point>* getGoalState(vector<State<Point>*> searchable, Point goal);

    void initialSearchable(vector<State<Point>*> &searchable, int i, vector<string> data);
};


#endif //SERVERSPROJECT_MYCLIENTHANDLER_H
