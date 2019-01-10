//
// Created by noam on 1/3/19.
//

#include "FileCacheManager.h"

string FileCacheManager::getSolution(string problem) {
    return pAndS.find(problem)->second;
}

bool FileCacheManager::doWeHaveSolution(string problem) {
    for (auto p : pAndS) {
        if (p.first == problem) {
            return true;
        } else {
            return false;
        }
    }
}

void FileCacheManager::makeMap() {
    ifstream file;
    string buffer;
    vector<string> allData;
    file.open("data.txt", ifstream::in | ifstream::app);

    if (!file) {
        throw "Failed opening file";
    }
    while (getline(file, buffer)) {
        allData = split(buffer);
        pAndS.insert(pair<string, string>(allData[0], allData[1]));
    }

    file.close();
}


vector<string> FileCacheManager::split(string buffer) {
    //split the line
    vector<string> data;
    size_t pos = START_STRING;
    int i = START_STRING;
    string delimiter = DELIMITER2;
    while ((pos = buffer.find(delimiter)) != string::npos) {
        data.push_back(buffer.substr(START_STRING, pos));
        buffer.erase(START_STRING, pos + delimiter.length());
        i++;
    }
    data.push_back(buffer.substr(START_STRING, pos));
    return data;
}

void FileCacheManager::addSolToMap(string problem, string solution) {
    pAndS.insert(pair<string, string>(problem, solution));
}

void FileCacheManager::writeInfo(string prob, string solut) {
    ofstream writeToFile;
    writeToFile.open("data.txt", ofstream::out |ofstream::app);
    if (!writeToFile) {
        throw "Failed opening file";
    }
    writeToFile << prob << DELIMITER2 << solut << endl;
    writeToFile.close();
}