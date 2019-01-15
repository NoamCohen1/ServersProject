#ifndef SERVERSPROJECT_CLIENTHANDLER_H
#define SERVERSPROJECT_CLIENTHANDLER_H

#include <iostream>
#include <ostream>
#include "Solver.h"
#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>

#include <string.h>
#include <vector>

#include <sys/socket.h>
#include "CacheManager.h"
#include "Point.h"
#include "State.h"
#include "Searchable.h"
#include "Matrix.h"

using namespace std;

class ClientHandler {
public:
    virtual void handleClient(int sockfd) = 0;
};

#endif //SERVERSPROJECT_CLIENTHANDLER_H
