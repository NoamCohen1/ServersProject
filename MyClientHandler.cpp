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
                            printf("Next command is [%s]\n", buff.c_str());
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



            // read the matrix
//            bzero(buffer, 256);
//            n = read(sockfd, buffer, 255);
//            if (n < 0) {
//                perror("ERROR reading from socket");
//                exit(1);            //vector<string> info;
//
//            }
//
//            size_t pos = 0;
//            string delimiter2 = "\n";
//            buff += buffer;
//            pos = buff.find(delimiter2);
//            leftOvers += buff.substr((0, pos));
//            // to remove the \n from the beginning of the string
//            leftOvers = leftOvers.substr(1);
//            buff.erase(pos + delimiter2.length() - 1);
//
//            if (buff == "end") {
//                break;
//            }
//            problem += "(";
//            problem += buff;
//            problem += ")";
//            data = split(buff);
//            temps.push_back(data);
//            data.clear();
//
//            buff = "";
//            buff += leftOvers;
//            leftOvers = "";
        }
        cout <<"yay1"<<endl;
        for (int j = 0; j < (temps.size() - 2); ++j) {
            this->initialSearchable(searchable, j, temps[j]);
        }
        Point initial(stoi((temps[temps.size() - 2])[0]), stoi((temps[temps.size() - 2])[1]));
        data.clear();
        Point goal(stoi((temps[temps.size() - 1])[0]), stoi((temps[temps.size() - 1])[1]));
        data.clear();
        cout <<"yay2"<<endl;
        Searchable<Point> *searchable1 = new Matrix(searchable, this->getInitialState(searchable, initial),
                                                    this->getGoalState(searchable, goal));
        cout <<"yay3"<<endl;

        //get solution
        if (this->cacheManager->doWeHaveSolution(problem)) {
            cout <<"yay4"<<endl;

            string str = this->cacheManager->getSolution(problem);
            cout <<"yay5"<<endl;

            result = const_cast<char *>(str.c_str());
            cout <<"yay6"<<endl;

            //printf("Here is the message after: %s\n", result);
            n = write(sockfd, result, strlen(result));
        } else {
            cout <<"yay7"<<endl;

            string solution = this->solver->solve(searchable1);
            cout <<"yay8"<<endl;

            this->cacheManager->addSolToMap(problem, solution);
            cout <<"yay9"<<endl;

            result = const_cast<char *>(solution.c_str());
            cout <<"yay10"<<endl;

            this->cacheManager->writeInfo(problem, result);
            cout <<"yay11"<<endl;

            //printf("Here is the message after: %s\n", result);
            n = write(sockfd, result, strlen(result));
        }
        cout <<"yay12"<<endl;

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