#ifndef SERVERSPROJECT_SOLVER_H
#define SERVERSPROJECT_SOLVER_H

template<class Prob, class Solu>
class Solver {
public:
    virtual Solu solve(Prob p) = 0;

    virtual ~Solver() = default;
};

#endif //SERVERSPROJECT_SOLVER_H
