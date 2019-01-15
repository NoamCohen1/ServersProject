//
// Created by gal on 1/13/19.
//

#ifndef SERVERSPROJECT_MYPARALLELSERVER_H
#define SERVERSPROJECT_MYPARALLELSERVER_H

#include <netinet/in.h>
#include <strings.h>
#include <unistd.h>
#include <thread>
#include "Server.h"
#include "MyClientHandler.h"

class MyParallelServer : public server_side::Server {
    struct info *paramInfo = new info();
    vector<pthread_t> threadList;
    int port;
    int sockfd;
    int serverfd;
    vector <pthread_t> threads;
public:
    void open(int port, ClientHandler *cH);

    void stop();

    static void* threadFunc (void* data);
};


#endif //SERVERSPROJECT_MYPARALLELSERVER_H
