#ifndef WEAK6_LINKED_H
#define WEAK6_LINKED_H


struct node {
    struct node *next;
    int data;
};

void insert_front(node **head, int data);

void print_list(node *head);

void insert_last(node **head, int data);

int search(node **head, int data);

int delete_(node **head, int data);

int delete_front(node **head);

void invert(node **head);

void lsort(node **head);

node *merge(node **a, node **b);

int cmp(int a, int b);

#endif //WEAK6_LINKED_H
