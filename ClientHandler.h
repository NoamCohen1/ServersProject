//
// Created by noam on 1/3/19.
//

#ifndef SERVERSPROJECT_CLIENTHANDLER_H
#define SERVERSPROJECT_CLIENTHANDLER_H

#include <iostream>
#include <ostream>
#include "Solver.h"
#include "CacheManager.h"
using namespace std;

class ClientHandler {
    Solver<string, string>* solver;
    CacheManager* cacheManager;
public:
    virtual void handleClient(int sockfd) = 0;

};
#endif //SERVERSPROJECT_CLIENTHANDLER_H
