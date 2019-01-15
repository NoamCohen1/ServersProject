//#include "MyTestClientHandler.h"
//
//void MyTestClientHandler::handleClient(int sockfd) {
//    char buffer[256];
//     int n;
//     char* result;
//     if (sockfd < 0) {
//         perror("ERROR on accept");
//         exit(1);
//     }
//
//     while (true) {
//         /* If connection is established then start communicating */
//         bzero(buffer, 256);
//         n = read(sockfd, buffer, 255);
//
//         if (n < 0) {
//             perror("ERROR reading from socket");
//             exit(1);
//         }
//
//         if (strcmp(buffer,"end") == 0) {
//             return;
//         }
//
//         printf("Here is the message: %s\n", buffer);
//
//
//         //get solution
//         if (this->fileCacheManager->doWeHaveSolution(buffer)) {
//             string str = this->fileCacheManager->getSolution(buffer);
//             result = const_cast<char *>(str.c_str());
//
//         } else {
//             string solution = this->solver->solve(buffer);
//             this->fileCacheManager->addSolToMap(buffer, solution);
//             result = const_cast<char *>(solution.c_str());
//             this->fileCacheManager->writeInfo(buffer, result);
//         }
//
//         printf("Here is the message after: %s\n", result);
//
//         n = write(sockfd, result, strlen(result));
//
//
//         if (n < 0) {
//             perror("ERROR writing to socket");
//             exit(1);
//         }
//
//
//
//         /* Write a response to the client */
//         /*n = write(sockfd, "I got your message", 18);
//
//         if (n < 0) {
//             perror("ERROR writing to socket");
//             exit(1);
//         }*/
//     }
//
//}
