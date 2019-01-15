#ifndef SERVERSPROJECT_MYSERIALSERVER_H
#define SERVERSPROJECT_MYSERIALSERVER_H

#include "Server.h"

using namespace server_side;

class MySerialServer : public Server {
public:
    virtual void open(int port, ClientHandler *handler);

    static void openSocket(int port, ClientHandler *handler);

    virtual void stop();
};

#endif //SERVERSPROJECT_MYSERIALSERVER_H
