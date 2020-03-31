#include <string>
#include <climits>
using namespace std;

#ifndef PRIORITY_QUEUE_ELEMENT_H_
#define PRIORITY_QUEUE_ELEMENT_H_


class PriorityQueueElement {

public:

    int priority;
    string item;


    PriorityQueueElement(string item, int priority) {
        this->item = item;
        this->priority = priority;
    }

    int getPriority() {
        return priority;
    }

    string getItem() {
        return item;
    }

    string toString(){
        return item;
    }

    bool operator==(const string& obj) const{
        return (obj.compare(this->item)==0);
    }
};

#endif