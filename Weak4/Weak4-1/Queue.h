//
// Created by 변승우 on 2022/10/09.
//

#ifndef WEAK4_QUEUE_H
#define WEAK4_QUEUE_H
#include "Array.h"

template<typename T>
class Queue : public Array<T>{
    // private front, rear 변수 선언
    int front;
    int rear;
public:
    Queue();
    bool isFull();
    bool isEmpty();
    T pop();
    void push();
    void draw();
};

#include "Queue.hpp"
#endif //WEAK4_QUEUE_H
