#include "FileCacheManager.h"

string FileCacheManager::getSolution(string problem) {
    pthread_mutex_lock(&mutex);
    string result = pAndS.find(problem)->second;
    pthread_mutex_unlock(&mutex);
    return result;
}

bool FileCacheManager::doWeHaveSolution(string problem) {
    pthread_mutex_lock(&mutex);
    for (auto p : pAndS) {
        if (p.first == problem) {
            pthread_mutex_unlock(&mutex);
            return true;
        }
    }
    pthread_mutex_unlock(&mutex);
    return false;
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
        pthread_mutex_lock(&mutex);
        pAndS.insert(pair<string, string>(allData[0], allData[1]));
        pthread_mutex_unlock(&mutex);
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
    pthread_mutex_lock(&mutex);
    pAndS.insert(pair<string, string>(problem, solution));
    pthread_mutex_unlock(&mutex);
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