#ifndef SERVERSPROJECT_MYPARALLELSERVER_H
#define SERVERSPROJECT_MYPARALLELSERVER_H

#include <netinet/in.h>
#include <strings.h>
#include <unistd.h>
#include <thread>
#include "Server.h"
#include "MyClientHandler.h"

using namespace server_side;

class MyParallelServer : public Server {
    struct info *paramInfo = new info();
    vector <pthread_t> threads;
public:
    void open(int port, ClientHandler *cH);

    void stop();

    static void* threadFunc (void* data);
};

#endif //SERVERSPROJECT_MYPARALLELSERVER_H
