//
// Created by noam on 1/3/19.
//

#ifndef SERVERSPROJECT_FILECACHEMANAGER_H
#define SERVERSPROJECT_FILECACHEMANAGER_H

#include "CacheManager.h"
#include <iostream>
#include <fstream>
#include <vector>

#define START_STRING 0
#define DELIMITER "$"


class FileCacheManager : public CacheManager {

public:
    FileCacheManager() {
        makeMap();
    }

    virtual bool doWeHaveSolution(string problem);

    virtual string getSolution(string problem);

    vector<string> split(string buffer);

    void makeMap();

    void addSolToMap(string problem, string solution);

    virtual void writeInfo(string problem, string solution);
};


#endif //SERVERSPROJECT_FILECACHEMANAGER_H
