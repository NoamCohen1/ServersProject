//
// Created by noam on 1/3/19.
//

#ifndef SERVERSPROJECT_CACHEMANAGER_H
#define SERVERSPROJECT_CACHEMANAGER_H

#include <string>
#include <map>
using namespace std;
class CacheManager {
protected:
    map <string, string> pAndS;
public:
    virtual bool doWeHaveSolution(string problem) = 0;

    virtual string getSolution(string problem) = 0;

    virtual void writeInfo(string problem, string solution) = 0;

    virtual void addSolToMap(string problem, string solution) = 0;

};

#endif //SERVERSPROJECT_CACHEMANAGER_H
