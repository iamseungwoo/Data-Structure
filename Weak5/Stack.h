//
// Created by 변승우 on 2022/10/14.
//

#ifndef WEAK5_STACK_H
#define WEAK5_STACK_H

#include <iostream>


template<typename T>
class Stack {
    T *stack;
    int top;
    int size;
public:
    Stack() {
        top = -1;
        size = 10;
        stack = new T[size];
    }

    T pop() {
        return stack[top--];
    }

    void push(T item) {
        if (top + 1 == size) {
            size <<= 1;
            stack = new T[size];
        }
        stack[++top] = item;
    }

    void showStack() {
        for (int i = 0; i <= top; i++) {
            std::cout << stack[i] << "  ";
        }
        std::cout << "           " << top - 1 << "\n";
    }

    int get_top() {
        return top;
    }
    T get(int idx) {
        return stack[idx];
    }
};


#endif //WEAK5_STACK_H
