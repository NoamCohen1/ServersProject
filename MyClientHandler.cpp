//
// Created by gal on 1/9/19.
//

#include "MyClientHandler.h"

void MyClientHandler::handleClient(int sockfd) {
    char buffer[256];
    char *result;
    int n;
    //int howManySearchables = 0;
    int searchableSize = 0;
    int i = 0;
    vector<string> data;
    vector<State<Point>*> searchable;
    string problem = "";

    if (sockfd < 0) {
        perror("ERROR on accept");
        exit(1);
    }

//    /* If connection is established then start communicating */
//    bzero(buffer, 256);
//    n = read(sockfd, buffer, 255);
//    if (n < 0) {
//        perror("ERROR reading from socket");
//        exit(1);
//    }

    //howManySearchables = stoi(buffer);

    while (true) {
        //while (howManySearchables != 0) {
        problem = "";
        searchable.clear();
        /* If connection is established then start communicating */
        // read the size
        bzero(buffer, 256);
        n = read(sockfd, buffer, 255);
        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }
        if (strcmp(buffer, "end") == 0) {
            return;
        }
        searchableSize = stoi(buffer);

        // read initial point
        bzero(buffer, 256);
        n = read(sockfd, buffer, 255);
        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }
        problem += buffer;
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
        problem += buffer;
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
            problem += buffer;
            data = split(buffer);
            this->initialSearchable(searchable, i, data);
            data.clear();
            ++i;
        }

        Searchable<Point>* searchable1 = new Matrix(searchable, this->getInitialState(searchable, initial), this->getGoalState(searchable, goal));


        //get solution
        if (this->cacheManager->doWeHaveSolution(problem)) {
            string str = this->cacheManager->getSolution(problem);
            result = const_cast<char *>(str.c_str());

        } else {
            string solution = this->solver->solve(searchable1);
            this->cacheManager->addSolToMap(problem, solution);
            result = const_cast<char *>(solution.c_str());
            this->cacheManager->writeInfo(problem, result);
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
        Point point(searchable[i]->getState().getI(), searchable[i]->getState().getJ());
        if (point == initial) {
            return searchable[i];
        }
    }
}

State<Point>* MyClientHandler::getGoalState(vector<State<Point> *> searchable, Point goal) {
    for (int i = 0; i < searchable.size(); ++i) {
        Point point(searchable[i]->getState().getI(), searchable[i]->getState().getJ());
        if (point == goal) {
            return searchable[i];
        }
    }
}

void MyClientHandler::initialSearchable(vector<State<Point>*> &searchable, int i, vector<string> data) {
    for (int j = 0; j < data.size(); ++j) {
        State<Point>* state = new State<Point>(Point(i, j), stod(data[j]));
        searchable.push_back(state);
    }
}

vector<pair<double, pair<int, int>>> MyClientHandler::makePairs(vector<State<Point> *> searchable) {
    vector<pair<double, pair<int, int>>> result;
    for (int i = 0; i < searchable.size(); ++i) {
        pair<int, int> pair1 = make_pair(searchable[i]->getState().getI(), searchable[i]->getState().getJ());
        result.push_back(make_pair(searchable[i]->getCost(), pair1));
    }
    return result;
}

pair<double, pair<int, int>> MyClientHandler::makePairsOfGAndI(State<Point> *state) {
    pair<double, pair<int, int>> result;
    pair<int, int> pair1 = make_pair(state->getState().getI(), state->getState().getJ());
    result = make_pair(state->getCost(), pair1);
    return result;
}