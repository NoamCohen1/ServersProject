//
// Created by gal on 1/7/19.
//

#ifndef SERVERSPROJECT_SEARCHER_H
#define SERVERSPROJECT_SEARCHER_H

#include <vector>
#include <string>
#include "Searchable.h"

using namespace std;

template <class Solu>
class Searcher {
public:
    virtual vector<State<Solu>*> search(Searchable<Solu> searchable) = 0;
};

#endif //SERVERSPROJECT_SEARCHER_H
