#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

// 스택 초기화
void StackInit(stack *st) {
    st->top = NULL;
}

void SPush(stack *st, int data) {
    node *newNode = (node *) malloc(sizeof(node));
    newNode->data = data;
    newNode->next = st->top;

    st->top=newNode;
}

int SPop(stack *st) {
    if (st->top == NULL) {
        return -1;
    }
    int tdata = st->top->data;
    node * tnode = st->top;

    st->top = st->top->next;
    free(tnode);

    return tdata;
}

void print_stack(stack st) {
    printf("HEAD->");
    for (; st.top!=NULL; st.top=st.top->next) {
        printf("%d->",st.top->data);
    }
    printf("NULL\n");
}