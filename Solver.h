#ifndef SERVERSPROJECT_SOLVER_H
#define SERVERSPROJECT_SOLVER_H

template<class Prob, class Solu>
class Solver {
public:
    virtual Solu solve(Prob p) = 0;
};

#endif //SERVERSPROJECT_SOLVER_H
