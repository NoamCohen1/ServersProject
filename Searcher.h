//
// Created by gal on 1/7/19.
//

#ifndef SERVERSPROJECT_SEARCHER_H
#define SERVERSPROJECT_SEARCHER_H

#include <vector>
#include <string>
#include "Searchable.h"

using namespace std;

template <class T>
class Searcher {
public:
    virtual vector<State<T>*> search(Searchable<T>* searchable) = 0;
};

#endif //SERVERSPROJECT_SEARCHER_H
