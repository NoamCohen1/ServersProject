#include <iostream>
#include "MySerialServer.h"
#include "ClientHandler.h"
#include "MyTestClientHandler.h"
#include "Solver.h"
#include "StringReverser.h"
int main() {
    std::cout << "Hello, World!" << std::endl;
    MySerialServer* mySerialServer = new MySerialServer();
    Solver<string, string>* solver = new StringReverser();
    FileCacheManager* fileCacheManager = new FileCacheManager();
    ClientHandler* clientHandler = new MyTestClientHandler(solver, fileCacheManager);
    mySerialServer->open(5400, clientHandler);
    //string g = "as";
    //string f = "jk";
    //fileCacheManager->writeInfo(g, f);
    while (true) {}
    return 0;
}