#include <iostream>
#include <unordered_map>
#include <vector>
#include "PriorirtyQueueElement.h"
using namespace std;

#ifndef PRIORITY_QUEUE_H_
#define PRIORITY_QUEUE_H_

template<class T>
class PriorityQueue {

private:
    vector<PriorityQueueElement<T>*> contents;
    int currentSize;
    unordered_map<T, int> itemToHeapIndex;

public:

    PriorityQueue() {
        currentSize = 0;
    }

    T getMinimumItem() {
        return contents[0]->item;
    }

    int getMinimumPriority() {
        return contents[0]->priority;
    }

    int getSize() {
        return currentSize;
    }

    void deleteMinimum() {

        if (currentSize == 0)
            throw "Priority queue is empty.";
        else if (currentSize == 1) {
            itemToHeapIndex.erase(contents[0]->item);
            currentSize--;
            contents.pop_back();
            return;
        }

        itemToHeapIndex.erase(contents[0]->item);
        itemToHeapIndex.erase(contents[--currentSize]->item);
        contents[0] = contents[currentSize];
        contents.pop_back();
        itemToHeapIndex[contents[0]->item] = 0;
        siftDown(0);
    }

    void setPriority(T item, int priority) {
        if (itemToHeapIndex.find(item) == itemToHeapIndex.end())
            insert(item, priority);
        else {
            int itemIndex = itemToHeapIndex[item];
            if (contents[itemIndex]->priority == priority)
                return;
            if (contents[itemIndex]->priority > priority) {
                contents[itemIndex]->priority = priority;
                siftUp(itemIndex);
            } else {
                contents[itemIndex]->priority = priority;
                siftDown(itemIndex);
            }
        }
    }

private:

    void insert(T item, int priority) {
        int index = currentSize++;
        contents.push_back(new PriorityQueueElement<T>(item, priority));
        itemToHeapIndex[item] = index;
        siftUp(index);
    }

    void siftDown(int index) {
        int leftIndex = index * 2 + 1, rightIndex = leftIndex + 1;
        while (leftIndex < currentSize) {
            int leftValue = contents[leftIndex]->priority;
            if (rightIndex < currentSize) {
                int rightValue = contents[rightIndex]->priority;
                if (leftValue < rightValue
                    && leftValue < contents[index]->priority) {
                    swap(index, leftIndex);
                    index = leftIndex;
                } else if (rightValue < contents[index]->priority) {
                    swap(index, rightIndex);
                    index = rightIndex;
                } else
                    break;
            } else if (leftValue < contents[index]->priority) {
                swap(index, leftIndex);
                index = leftIndex;
            } else
                break;
            leftIndex = index * 2 + 1;
            rightIndex = leftIndex + 1;
        }
    }

    void siftUp(int index) {
        while (index > 0
               && contents[parent(index)]->priority > contents[index]->priority) {
            swap(index, parent(index));
            index = parent(index);
        }
    }

    void swap(int index1, int index2) {
        itemToHeapIndex.erase(contents[index1]->item);
        itemToHeapIndex.erase(contents[index2]->item);

        PriorityQueueElement<T> *item = contents[index1];
        contents[index1] = contents[index2];
        contents[index2] = item;

        itemToHeapIndex[contents[index1]->item] = index1;
        itemToHeapIndex[contents[index2]->item] = index2;
    }

    int parent(int index) {
        return (index - 1) / 2;
    }

public:

    void print() {
        if (0 == currentSize) {
            cout << "[]";
            return;
        }
        cout << "[";
        for (int i = 0; i < currentSize - 1; i++) {
            cout << contents[i].toString() << ", ";
        }
        cout << contents[currentSize - 1].toString() << "]";
    }
};

#endif