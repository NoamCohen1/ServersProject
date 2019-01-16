#ifndef SERVERSPROJECT_MYPARALLELSERVER_H
#define SERVERSPROJECT_MYPARALLELSERVER_H

#include <netinet/in.h>
#include <strings.h>
#include <unistd.h>
#include <thread>
#include <stack>
#include "Server.h"
#include "MyClientHandler.h"

using namespace server_side;

class MyParallelServer : public Server {
    stack<pthread_t> threads;
    int sockfd{};
    int port{};
    ClientHandler* clientHandler{};
public:
    void open(int port, ClientHandler *cH);

    void stop();

    static void *startThreadClient(void *data);

    void start();

    virtual ~MyParallelServer() = default;
};

#endif //SERVERSPROJECT_MYPARALLELSERVER_H
