#include "MyParallelServer.h"

struct info {
    int sock;
    ClientHandler *clientHandler;
};

void MyParallelServer::open(int port, ClientHandler *clientHandler) {
    this->port = port;
    this->clientHandler = clientHandler;
    int server_fd;
    struct sockaddr_in address{};
    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    int n = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &n, sizeof(int));
    if (bind(sockfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        perror("socket bind");
        exit(1);
    }

    if (listen(sockfd, 5) == -1) {
        perror("socket listen");
        exit(1);
    }
    start();
}

void MyParallelServer::stop() {
    while (!this->threads.empty()) {
        pthread_join(this->threads.top(), nullptr);
        this->threads.pop();
    }
    close(this->sockfd);
}

void *MyParallelServer::startThreadClient(void *params) {
    auto data = (info *) params;
    data->clientHandler->handleClient(data->sock);
    delete data;
}

void MyParallelServer::start() {
    sockaddr_in address{};
    int addrlen = sizeof(address);

    timeval timeout;
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(timeout));

    int new_socket;
    while (true) {
        timeout.tv_sec = 10;
        timeout.tv_usec = 0;
        setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(timeout));
        if ((new_socket = accept(sockfd,
                                 (struct sockaddr *) &address,
                                 (socklen_t *) &addrlen)) < 0) {
            if (errno == EWOULDBLOCK || errno == EAGAIN) {
                break;
            }
            perror("accept");
            exit(EXIT_FAILURE);
        }
        setsockopt(new_socket, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(timeout));
        auto data = new info;
        data->clientHandler = this->clientHandler;
        data->sock = new_socket;
        pthread_t trid;
        if (pthread_create(&trid, nullptr, startThreadClient, data) < 0) {
            perror("error on creating thread");
            exit(1);
        }
        this->threads.push(trid);
    }
    stop();
}