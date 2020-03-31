//
// Created by ryanj on 3/29/2020.
//
#include "Edge.h"
#ifndef SHORTESTPATHTICKETTORIDE_OUTDEGREE_H
#define SHORTESTPATHTICKETTORIDE_OUTDEGREE_H

struct OutDegree{
    Edge* out;
    int outDegree;
    OutDegree(Edge* out,int outDegree){
        this->out=out;
        this->outDegree=outDegree;
    }
};

#endif //SHORTESTPATHTICKETTORIDE_OUTDEGREE_H
