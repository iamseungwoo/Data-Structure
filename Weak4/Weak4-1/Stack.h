//
// Created by 변승우 on 2022/10/09.
//

#ifndef WEAK4_STACK_H
#define WEAK4_STACK_H

#include "Array.h"

template<typename T>
class Stack : public Array<T>{
    int top;
public:
    Stack();
    void push();
    T pop();
    bool isFull();
    bool isEmpty();
    void draw();
};
#include "Stack.hpp"

#endif //WEAK4_STACK_H
