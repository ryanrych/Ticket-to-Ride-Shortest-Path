//
// Created by ryanj on 3/30/2020.
//
#include "Edge.h"

#ifndef SHORTESTPATHTICKETTORIDE_HASH_H
#define SHORTESTPATHTICKETTORIDE_HASH_H

class Hash {
public:
    size_t operator()(const string& s) const
    {
        return s.length();
    }
};


#endif //SHORTESTPATHTICKETTORIDE_HASH_H
