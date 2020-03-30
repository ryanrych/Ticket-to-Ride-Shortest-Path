//
// Created by ryanj on 3/29/2020.
//
#include "Edge.h"
#ifndef SHORTESTPATHTICKETTORIDE_OUTDEGREE_H
#define SHORTESTPATHTICKETTORIDE_OUTDEGREE_H

struct OutDegree{
    Edge* out;
    OutDegree(Edge* out){
        this->out=out;
    }
};

#endif //SHORTESTPATHTICKETTORIDE_OUTDEGREE_H
