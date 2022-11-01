//
// Created by 변승우 on 2022/10/28.
//

#ifndef WEAK6_QUEUE_H
#define WEAK6_QUEUE_H
#include "Linked.h"
struct queue {
    node *front;
    node *rear;
};

void initQ(queue *qu);

void addQ(queue *qu, int data);

int deleteQ(queue *qu);

int isEmpty(queue *qu);

void print_queue(queue qu);

#endif //WEAK6_QUEUE_H
