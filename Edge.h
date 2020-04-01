//
// Created by ryanj on 3/29/2020.
//

#ifndef SHORTESTPATHTICKETTORIDE_EDGE_H
#define SHORTESTPATHTICKETTORIDE_EDGE_H

struct Edge{
    string start;
    string destination;
    int weight;
    Edge(){
        start="";
        destination="";
        weight=-1;
    }
    Edge(string destination, int weight){
        start="";
        this->destination=destination;
        this->weight=weight;
    }
    Edge(string start,string destination,int weight){
        this->start=start;
        this->destination=destination;
        this->weight=weight;
    }
    bool operator<(const Edge& obj) const{
        return (obj.weight<=this->weight);
    }
    bool operator==(const Edge& obj) const{
        return ((obj.weight==this->weight)&&(obj.destination.compare(this->destination)==0) && (obj.start.compare(this->start)==0));
    }
};

#endif //SHORTESTPATHTICKETTORIDE_EDGE_H
