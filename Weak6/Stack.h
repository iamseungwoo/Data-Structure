//
// Created by 변승우 on 2022/10/28.
//

#ifndef WEAK6_STACK_H
#define WEAK6_STACK_H
#include "Linked.h"
struct stack {
    node *top;
};

void StackInit(stack *st);

void SPush(stack *st, int data);

int SPop(stack *st);

void print_stack(stack st);


#endif //WEAK6_STACK_H