//
// Created by noam on 1/3/19.
//


#ifndef SERVERSPROJECT_MYSERIALSERVER_H
#define SERVERSPROJECT_MYSERIALSERVER_H
#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>

#include <string.h>

#include <sys/socket.h>

#include "Server.h"

class MySerialServer : public Server {
public:
    virtual void open(int port, ClientHandler handler);

    virtual void stop();
};


#endif //SERVERSPROJECT_MYSERIALSERVER_H
