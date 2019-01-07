//
// Created by noam on 1/3/19.
//

#ifndef SERVERSPROJECT_SERVER_H
#define SERVERSPROJECT_SERVER_H

#include "ClientHandler.h"

class Server {
protected:
    bool stopLoop = false;
public:
    virtual void open(int port, ClientHandler handler) = 0;

    virtual void stop() = 0;
};

#endif //SERVERSPROJECT_SERVER_H
