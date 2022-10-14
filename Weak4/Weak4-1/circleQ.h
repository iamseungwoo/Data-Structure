//
// Created by 변승우 on 2022/10/09.
//

#ifndef WEAK4_CIRCLEQ_H
#define WEAK4_CIRCLEQ_H
#include "Array.h"
template<typename T>
class circleQ: Array<T>{
    // private front,rear 변수 선언
    int front;
    int rear;
public:
    circleQ();
    bool isEmpty();
    bool isFull();
    void push();
    T pop();
    void draw();
};

#include "circleQ.hpp"
#endif //WEAK4_CIRCLEQ_H
