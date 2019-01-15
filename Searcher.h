#ifndef SERVERSPROJECT_SEARCHER_H
#define SERVERSPROJECT_SEARCHER_H

#include <vector>
#include <string>
#include "Searchable.h"

using namespace std;

template<class T>
class Searcher {
public:
    virtual string search(Searchable<T> *searchable) = 0;
};

#endif //SERVERSPROJECT_SEARCHER_H
