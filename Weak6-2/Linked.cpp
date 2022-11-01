#include <stdio.h>
#include <stdlib.h>
#include "CircluarLinked.h"

// 비교 함수 a > b보다 크면 1반환 아니면 0반환
int cmp(int a, int b) {
    return a - b > 0 ? 1 : 0;
}

// 리스트 제일 앞에 추가하기
void insert_front(node **head, int data) {
    node *temp = (node *) malloc(sizeof(node));
    temp->data = data;

    if (*head == NULL) {
        *head = temp;
        (*head)->next = *head;
    } else {
        temp->next = (*head)->next;
        (*head)->next = temp;
    }
}

// 리스트 전체 출력
void print_list(node *head) {
    // head 노드 기억
    node *remb = head;
    printf("HEAD->");
    do {
        head = head->next;
        printf("%d->", head->data);
    } while(head != remb);
    printf("NULL\n");
}

// 리스트 끝에 출력
void insert_last(node **head, int data) {
    node *temp = (node *) malloc(sizeof(node));
    temp->data = data;
    // 리스트가 비어있을 경우 head에 input
    if (*head == NULL) {
        *head = temp;
        (*head)->next = *head;
    }
    else {
        temp->next = (*head)->next;
        (*head)->next = temp;
        *head = (*head)->next;
    }
}

// 찾기 함수
int search(node *head, int data) {
    node *prev = head->next;
    // 인덱스는 0번 부터 시작
    int idx = 0;
    // head 값 temp에 복사해서 값을 찾으면 idx 반환한다.
    do {
        head = head->next;
        if (head->data == data) {
            return idx;
        }
        ++idx;
    } while (head != prev);
    // 못 찾으면 -1을 반환
    return -1;
}

// 제일 앞 노드 삭제
int delete_front(node **head) {
    // head가 비어있으면 -1 반환
    if (*head == NULL) {
        return -1;
    }
    // head 노드 temp에 저장
    node *temp = (*head)->next;
    (*head)->next = (*head)->next->next;
    // head 노드의 데이터 저장
    int del = temp->data;

    free(temp);
    return del;
}

// data와 일치하는 node 삭제
int delete_(node **head, int data) {

    // 리스트가 비었으면 -1 반환
    if (*head == NULL) {
        return -1;
    }
    // 임시 노드 생성
    node *prev = *head;
    node *loop_node = *head;
    do {
        if (loop_node->next->data == data) {
            node *temp = loop_node->next;
            loop_node->next = loop_node->next->next;
            free(temp);
            return data;
        }
        loop_node = loop_node->next;
    } while (loop_node != prev);
    // 삭제 못하면 -1 반환
    return -1;
}

// 역순 시킨다.
void invert(node **head) {
    *head = (*head)->next;
    node *prev = *head;
    node *q = NULL, *r;
    do {
        r = q;
        q = *head;
        *head = (*head)->next;
        q->next = r;
    } while (*head != prev);
    prev->next = q;
    q = prev;
    print_list(q);
    *head = q;
}

// 링크드 리스트 정렬 함수
void lsort(node **head) {
    // *head가 NULL이면 끝냄
    if (*head == NULL) {
        return;
    }
    // 선택 정렬을 하는데 노드를 바꾸는게 아니라 data만 바꾼다.
    for (node *i = *head; i->next != NULL; i = i->next) {
        for (node *j = i->next; j != NULL; j = j->next) {
            if (cmp(i->data, j->data)) {
                int temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
}