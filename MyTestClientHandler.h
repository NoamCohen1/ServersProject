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

class MyTestClientHandler : public ClientHandler {
    Solver solver;
    CacheManager cacheManager;
public:
    virtual void handleClient(istream &inputStream, ostream &outputStream);

    void solveProblem(int sockfd);

};


#endif //SERVERSPROJECT_MYTESTCLIENTHANDLER_H
