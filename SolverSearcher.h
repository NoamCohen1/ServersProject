//
// Created by gal on 1/8/19.
//

#ifndef SERVERSPROJECT_SOLVERSEARCHER_H
#define SERVERSPROJECT_SOLVERSEARCHER_H

#include "Solver.h"
#include "Searcher.h"
#include "Point.h"

class SolverSearcher : public Solver<Searchable<Point>*, string> {
    Searcher<Point>* searcher;
public:
    SolverSearcher(Searcher<Point> *searcher) : searcher(searcher) {}

//    SolverSearcher(Searcher<Point>* searcher1) {
//        this->searcher = searcher1;
//    }

    virtual string solve(Searchable<Point>* p) {
        return this->searcher->search(p);
    }
};

#endif //SERVERSPROJECT_SOLVERSEARCHER_H
