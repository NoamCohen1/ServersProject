//
// Created by gal on 1/13/19.
//

#ifndef SERVERSPROJECT_MYPARALLELSERVER_H
#define SERVERSPROJECT_MYPARALLELSERVER_H

#include <cstring>
#include "Server.h"
class MyParallelServer: public Server{
public:
    virtual void open(int port, ClientHandler* handler);

    static void openSocket(int port, ClientHandler* handler);

    virtual void stop();
};


#endif //SERVERSPROJECT_MYPARALLELSERVER_H
