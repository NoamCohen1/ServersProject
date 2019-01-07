//
// Created by gal on 1/7/19.
//

#include <algorithm>
#include "StringReverser.h"


string StringReverser::solve(string origin) {
    reverse(origin.begin(), origin.end());
    return origin;
}