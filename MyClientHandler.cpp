//
// Created by gal on 1/9/19.
//

#include "MyClientHandler.h"

void MyClientHandler::handleClient(int sockfd) {
    char buffer[256];
    char *result;
    int n;
    int howManySearchables = 0;
    int searchableSize = 0;
    int i = 0;
    vector<string> data;
    vector<State<Point>*> searchable;

    if (sockfd < 0) {
        perror("ERROR on accept");
        exit(1);
    }

    /* If connection is established then start communicating */
    bzero(buffer, 256);
    n = read(sockfd, buffer, 255);
    if (n < 0) {
        perror("ERROR reading from socket");
        exit(1);
    }

    howManySearchables = stoi(buffer);

    while (howManySearchables != 0) {
        /* If connection is established then start communicating */
        bzero(buffer, 256);
        n = read(sockfd, buffer, 255);
        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }

        printf("Here is the message: %s\n", buffer);

        // read the size
        bzero(buffer, 256);
        n = read(sockfd, buffer, 255);
        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }
        searchableSize = stoi(buffer);

        // read initial point
        bzero(buffer, 256);
        n = read(sockfd, buffer, 255);
        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }
        data = split(buffer);
        Point initial(stoi(data[0]), stoi(data[1]));
        data.clear();

        // read goal point
        bzero(buffer, 256);
        n = read(sockfd, buffer, 255);
        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }
        data = split(buffer);
        Point goal(stoi(data[0]), stoi(data[1]));
        data.clear();

        while (i != searchableSize) {
            // read the matrix
            bzero(buffer, 256);
            n = read(sockfd, buffer, 255);
            if (n < 0) {
                perror("ERROR reading from socket");
                exit(1);
            }
            data = split(buffer);
            this->initialSearchable(searchable, i, data, initial, goal);
            data.clear();
            ++i;
        }


        Searchable<Point>* searchable1 = new Matrix(searchable, this->getInitialState(searchable, initial), this->getGoalState(searchable, goal));

        //get solution
        if (this->cacheManager->doWeHaveSolution(buffer)) {
            string str = this->cacheManager->getSolution(buffer);
            result = const_cast<char *>(str.c_str());

        } else {
            string solution = this->solver->solve(buffer);
            this->cacheManager->addSolToMap(buffer, solution);
            result = const_cast<char *>(solution.c_str());
            this->cacheManager->writeInfo(buffer, result);
        }

        printf("Here is the message after: %s\n", result);

        n = write(sockfd, result, strlen(result));

        if (n < 0) {
            perror("ERROR writing to socket");
            exit(1);
        }
    }
}

vector<string> MyClientHandler::split(string buffer) {
    //split the line
    vector<string> data;
    size_t pos = START_STRING;
    int i = START_STRING;
    string delimiter = DELIMITER;
    while ((pos = buffer.find(delimiter)) != string::npos) {
        data.push_back(buffer.substr(START_STRING, pos));
        buffer.erase(START_STRING, pos + delimiter.length());
        i++;
    }
    data.push_back(buffer.substr(START_STRING, pos));
    return data;
}

State<Point>* MyClientHandler::getInitialState(vector<State<Point> *> searchable, Point initial) {
    for (int i = 0; i < searchable.size(); ++i) {
        Point point(searchable[i]->getState()->getI(), searchable[i]->getState()->getJ());
        if (point == initial) {
            return searchable[i];
        }
    }
}

State<Point>* MyClientHandler::getGoalState(vector<State<Point> *> searchable, Point goal) {
    for (int i = 0; i < searchable.size(); ++i) {
        Point point(searchable[i]->getState()->getI(), searchable[i]->getState()->getJ());
        if (point == goal) {
            return searchable[i];
        }
    }
}

void MyClientHandler::initialSearchable(vector<State<Point>*> &searchable, int i, vector<string> data, Point initial, Point goal) {
    for (int j = 0; j < data.size(); ++j) {
        Point pointToCompare(i, j);
        State<Point>* state = new State<Point>(new Point(i, j), stod(data[j]));
        if (pointToCompare == initial) {

        }
    }
}