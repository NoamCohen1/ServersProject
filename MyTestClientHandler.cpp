//
// Created by noam on 1/3/19.
//

#include "MyTestClientHandler.h"
 void MyTestClientHandler::handleClient(istream &inputStream, ostream &outputStream) {

}

void MyTestClientHandler::solveProblem(int sockfd) {
    char buffer[256];
    int  n;
    if (sockfd < 0) {
        perror("ERROR on accept");
        exit(1);
    }

    /* If connection is established then start communicating */
    bzero(buffer,256);
    n = read( sockfd,buffer,255 );

    if (n < 0) {
        perror("ERROR reading from socket");
        exit(1);
    }

    printf("Here is the message: %s\n",buffer);

    /* Write a response to the client */
    n = write(sockfd,"I got your message",18);

    if (n < 0) {
        perror("ERROR writing to socket");
        exit(1);
    }
}