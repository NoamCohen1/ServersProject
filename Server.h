//
// Created by noam on 1/3/19.
//

#ifndef SERVERSPROJECT_SERVER_H
#define SERVERSPROJECT_SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <thread>

#include "ClientHandler.h"

class Server {
protected:
    bool stopLoop = false;
public:
    virtual void open(int port, ClientHandler* handler) = 0;

    virtual void stop() = 0;
};

#endif //SERVERSPROJECT_SERVER_H
