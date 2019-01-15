#ifndef SERVERSPROJECT_STRINGREVERSER_H
#define SERVERSPROJECT_STRINGREVERSER_H

#include "Solver.h"
#include <string>

using namespace std;

class StringReverser : public Solver <string, string> {
public:
    string solve (string origin);
};

#endif //SERVERSPROJECT_STRINGREVERSER_H
