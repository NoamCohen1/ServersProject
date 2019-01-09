//
// Created by noam on 1/3/19.
//

#ifndef SERVERSPROJECT_SOLVER_H
#define SERVERSPROJECT_SOLVER_H
template <class Prob, class Solu>
class Solver {
public:
    //virtual Algorithm solve(Problem p) = 0;
    virtual Solu solve(Prob p) = 0;
};

#endif //SERVERSPROJECT_SOLVER_H
