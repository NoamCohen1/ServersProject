//
// Created by noam on 1/3/19.
//

#ifndef SERVERSPROJECT_MYSERIALSERVER_H
#define SERVERSPROJECT_MYSERIALSERVER_H

#include "Server.h"

class MySerialServer : public Server {
public:
    virtual void open(int port, ClientHandler handler);

    virtual void stop();
};


#endif //SERVERSPROJECT_MYSERIALSERVER_H
