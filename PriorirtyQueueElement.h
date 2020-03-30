#include <string>
#include <climits>
using namespace std;

#ifndef PRIORITY_QUEUE_ELEMENT_H_
#define PRIORITY_QUEUE_ELEMENT_H_

template<class T>
class PriorityQueueElement {

public:

    int priority;
    T item;

    PriorityQueueElement(T item, int priority) {
        this->item = item;
        this->priority = priority;
    }

    int getPriority() {
        return priority;
    }

    T getItem() {
        return item;
    }

    string toString() {
        return "<" + item->toString() + ", " + to_string(priority) + ">";
    }
};

#endif