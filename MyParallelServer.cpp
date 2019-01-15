#include "MyParallelServer.h"

void MyParallelServer::open(int port, ClientHandler *cH) {
    int sockfd, portno;
    struct sockaddr_in serv_addr;

    /* First call to socket() function */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }
    this->paramInfo->clientHandler=cH;
    /* Initialize socket structure */
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = port;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    /* Now bind the host address using bind() call.*/
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        exit(1);
    }
    struct sockaddr_in cli_addr;
    int clilen, cliSock;
    listen(sockfd, SOMAXCONN);
    clilen = sizeof(cli_addr);

    timeval timeout;
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;
    //setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(timeout));
    while (true){
        // Accept actual connection from the client
        cliSock = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t *) &clilen);
        this->paramInfo->sockfd = cliSock;
        if (cliSock < 0) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                stop();
                break;
            } else {
                perror("ERROR on accept");
                exit(1);
            }
        }
        if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(timeout)) == -1) {
            perror("ERROR on setting timeout");
        }
        pthread_t pthread;
        if(pthread_create(&pthread, nullptr,MyParallelServer::threadFunc,paramInfo)!=0){
            perror("thread failed");
        }
        this->threads.push_back(pthread);
    }
    return;
}

void *MyParallelServer::threadFunc(void *data) {
    struct info *paramInfo = (struct info *) data;
    paramInfo->clientHandler->handleClient(paramInfo->sockfd);
}

void MyParallelServer::stop() {
    for(int i = 0; i < this->threads.size(); ++i) {
        pthread_join(this->threads[i], nullptr);
    }
    return;
}