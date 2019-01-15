#ifndef SERVERSPROJECT_SOLVERSEARCHER_H
#define SERVERSPROJECT_SOLVERSEARCHER_H

#include "Solver.h"
#include "Searcher.h"
#include "Point.h"

class SolverSearcher : public Solver<Searchable<Point>*, string> {
    Searcher<Point>* searcher;
public:
    SolverSearcher(Searcher<Point> *searcher) : searcher(searcher) {}

    virtual string solve(Searchable<Point>* p) {
        return this->searcher->search(p);
    }
};

#endif //SERVERSPROJECT_SOLVERSEARCHER_H
