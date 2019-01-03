//
// Created by noam on 1/3/19.
//

#ifndef SERVERSPROJECT_MYTESTCLIENTHANDLER_H
#define SERVERSPROJECT_MYTESTCLIENTHANDLER_H

#include "ClientHandler.h"
#include "Solver.h"
#include "CacheManager.h"

class MyTestClientHandler : public ClientHandler {
    Solver solver;
    CacheManager cacheManager;
public:

};


#endif //SERVERSPROJECT_MYTESTCLIENTHANDLER_H
