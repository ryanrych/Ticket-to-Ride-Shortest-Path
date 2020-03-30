//
// Created by ryanj on 3/29/2020.
//

#ifndef SHORTESTPATHTICKETTORIDE_EDGE_H
#define SHORTESTPATHTICKETTORIDE_EDGE_H

struct Edge{
    string destination;
    int weight;
    Edge(){
        destination="";
        weight=-1;
    }
    Edge(string destination, int weight){
        this->destination=destination;
        this->weight=weight;
    }
    bool operator< (const Edge& edgeObj) const{
        if(edgeObj.weight < this->weight)
            return true;
    }
};

#endif //SHORTESTPATHTICKETTORIDE_EDGE_H
