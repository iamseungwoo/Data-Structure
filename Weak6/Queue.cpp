#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"

// front, rear 초기화
void initQ(queue *qu) {
    qu->front = NULL;
    qu->rear = NULL;
}

// queue 뒤에 rear에 추가
void addQ(queue *qu, int data) {
    node *newNode = (node *) malloc(sizeof(node));
    newNode->data = data;
    newNode->next = NULL;
    // 처음 add 할때는 front, rear 둘다 새로 추가되는 노드를 가리켜야함
    if (isEmpty(qu)) {
        qu->front = newNode;
        qu->rear = newNode;
    } else {
        qu->rear->next = newNode;
        qu->rear = qu->rear->next;
    }
}

// front 에 있는 노드 삭제
int deleteQ(queue *qu) {
    if (isEmpty(qu)) {
        return -1;
    }

    node *tempDel = qu->front;
    int delData = qu->front->data;
    qu->front = qu->front->next;

    free(tempDel);

    return delData;
}

// 비어있는 지 확인
int isEmpty(queue *qu) {
    return qu->front == NULL ? 1 : 0;
}

// 큐 출력
void print_queue(queue qu) {
    printf("HEAD->");
    for (; qu.front != NULL; qu.front = qu.front->next) {
        printf("%d->", qu.front->data);
    }
    printf("NULL\n");
}