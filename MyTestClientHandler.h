//
// Created by noam on 1/3/19.
//

#ifndef SERVERSPROJECT_MYTESTCLIENTHANDLER_H
#define SERVERSPROJECT_MYTESTCLIENTHANDLER_H

#include "ClientHandler.h"
#include "Solver.h"
#include "CacheManager.h"
#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>

#include <string.h>

#include <sys/socket.h>
#include "FileCacheManager.h"

class MyTestClientHandler : public ClientHandler {
    Solver<string, string>* solver;
    FileCacheManager* fileCacheManager;
public:
    MyTestClientHandler(Solver<string, string>* solver, FileCacheManager* fileCacheManager) {
        this->solver = solver;
        this->fileCacheManager = fileCacheManager;
    }
    virtual void handleClient(int sockfd);

};


#endif //SERVERSPROJECT_MYTESTCLIENTHANDLER_H
