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
    bool operator<(const Edge& obj) const{
        return (obj.weight<=this->weight);
    }
    bool operator==(const Edge& obj) const{
        return (obj.weight==this->weight)&&(obj.destination.compare(obj.destination)==0);
    }
};

#endif //SHORTESTPATHTICKETTORIDE_EDGE_H
