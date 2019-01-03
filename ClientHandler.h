//
// Created by noam on 1/3/19.
//

#ifndef SERVERSPROJECT_CLIENTHANDLER_H
#define SERVERSPROJECT_CLIENTHANDLER_H

#include <iostream>
#include <ostream>

using namespace std;

class ClientHandler {
public:
    virtual void handleClient(istream &inputStream, ostream &outputStream) = 0;
};
#endif //SERVERSPROJECT_CLIENTHANDLER_H
