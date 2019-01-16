#include "MyClientHandler.h"

void MyClientHandler::handleClient(int sockfd) {
    char buffer[256];
    char *result;
    int n;
    vector<string> data;
    vector<State<Point> *> searchable;
    vector<vector<string>> temps;
    string problem = "";

    if (sockfd < 0) {
        perror("ERROR on accept");
        exit(1);
    }

    while (true) {
        problem = "";
        searchable.clear();
        temps.clear();
        string buff = "";
        string leftOvers = "";
        /* If connection is established then start communicating */
        while (true) {
            char buffer[256];
            int numBytesRead = recv(sockfd, buffer, sizeof(buffer), 0);
            if (numBytesRead > 0) {
                for (int i = 0; i < numBytesRead; ++i) {
                    char c = buffer[i];
                    if (c == '\n') {
                        if (buff.length() > 0) {
                            //printf("Next command is [%s]\n", buff.c_str());
                            if (buff == "end") {
                                break;
                            }
                            problem += "(";
                            problem += buff;
                            problem += ")";
                            data = split(buff);
                            temps.push_back(data);
                            data.clear();
                            buff = "";
                        }
                    } else {
                        buff += c;
                    }
                }
            } else {
                printf("Socket closed or socket error!\n");
                break;
            }
            if (buff == "end") {
                buff = "";
                break;
            }
        }
        for (int j = 0; j < (temps.size() - 2); ++j) {
            this->initialSearchable(searchable, j, temps[j]);
        }
        Point initial(stoi((temps[temps.size() - 2])[0]), stoi((temps[temps.size() - 2])[1]));
        data.clear();
        Point goal(stoi((temps[temps.size() - 1])[0]), stoi((temps[temps.size() - 1])[1]));
        data.clear();
        Searchable<Point> *searchable1 = new Matrix(searchable, this->getInitialState(searchable, initial),
                                                    this->getGoalState(searchable, goal));
        //get solution
        if (this->cacheManager->doWeHaveSolution(problem)) {
            string str = this->cacheManager->getSolution(problem);
            result = const_cast<char *>(str.c_str());
            //printf("Here is the message after: %s\n", result);
            n = write(sockfd, result, strlen(result));
        } else {
            string solution = this->solver->solve(searchable1);
            this->cacheManager->addSolToMap(problem, solution);
            result = const_cast<char *>(solution.c_str());
            this->cacheManager->writeInfo(problem, result);
            //printf("Here is the message after: %s\n", result);
            n = write(sockfd, result, strlen(result));
        }
        if (n < 0) {
            perror("ERROR writing to socket");
            exit(1);
        }
        for (State<Point> *state : searchable1->getSearchable()) {
            delete (state);
        }
        delete (searchable1);
        break;
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

State<Point> *MyClientHandler::getInitialState(vector<State<Point> *> searchable, Point initial) {
    for (int i = 0; i < searchable.size(); ++i) {
        Point point(searchable[i]->getState().getI(), searchable[i]->getState().getJ());
        if (point == initial) {
            return searchable[i];
        }
    }
}

State<Point> *MyClientHandler::getGoalState(vector<State<Point> *> searchable, Point goal) {
    for (int i = 0; i < searchable.size(); ++i) {
        Point point(searchable[i]->getState().getI(), searchable[i]->getState().getJ());
        if (point == goal) {
            return searchable[i];
        }
    }
}

void MyClientHandler::initialSearchable(vector<State<Point> *> &searchable, int i, vector<string> data) {
    for (int j = 0; j < data.size(); ++j) {
        State<Point> *state = new State<Point>(Point(i, j), stod(data[j]));
        searchable.push_back(state);
    }
}