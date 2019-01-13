//
// Created by gal on 1/13/19.
//

#include "MyParallelServer.h"

void MyParallelServer::open(int port, ClientHandler *cH) {
    cout<<"hi 1"<<endl;
    int sockfd, portno;
    struct sockaddr_in serv_addr;

    /* First call to socket() function */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }
    this->passingData->sockfd = sockfd;
    this->passingData->clientHandler=cH;
    cout<<"hi 2"<<endl;
    /* Initialize socket structure */
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = port;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    cout<<"hi 3"<<endl;
    /* Now bind the host address using bind() call.*/
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        cout<<"hi 4"<<endl;
        perror("ERROR on binding");
        exit(1);
    }
    cout<<"hi 5"<<endl;
    struct sockaddr_in cli_addr;
    int clilen, cliSock;
    listen(sockfd, SOMAXCONN);
    cout<<"hi 6"<<endl;
    clilen = sizeof(cli_addr);

    timeval timeout;
    timeout.tv_sec = 10000;
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(timeout));
    cout<<"hi 7"<<endl;
    while (true) {

        // Accept actual connection from the client
        cliSock = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t *) &clilen);
        cout<<"hi 8"<<endl;
        if (cliSock < 0) {
            if (errno == EWOULDBLOCK) {
                cout << "TimeOut!" << endl;
                //stop();
            } else {
                perror("ERROR on accept");
                exit(1);
            }
        }
        cout<<"hi 9"<<endl;
        pthread_t pthread;
        if(pthread_create(&pthread, nullptr,MyParallelServer::threadManager,passingData)!=0){
            perror("thread failed");
        }
        cout<<"hi 10"<<endl;
        this->threads.push_back(pthread);
    }


}

void *MyParallelServer::threadManager(void *data) {
    cout<<"hi 11"<<endl;
    struct dataPass *passingData = (struct dataPass *) data;
    passingData->clientHandler->handlerClient(passingData->sockfd);
}

void MyParallelServer::stop() {
    for(int i=0;i<this->threads.size();++i){
        pthread_join(this->threads[i],NULL);
        //delete(this->threads[i]);
    }
}
