#include <stdio.h>
#include <stdlib.h>
#include "Linked.h"

// 비교 함수 a > b보다 크면 1반환 아니면 0반환
int cmp(int a, int b) {
    return a - b > 0 ? 1 : 0;
}

// 리스트 제일 앞에 추가하기
void insert_front(node **head, int data) {
    node *temp = (node *) malloc(sizeof(node));
    temp->data = data;
    temp->next = *head;
    *head = temp;
}

// 리스트 전체 출력
void print_list(node *head) {
    printf("HEAD->");
    for (; head != NULL; head = head->next) {
        printf("%d->", head->data);
    }
    printf("NULL\n");
}

// 리스트 끝에 출력
void insert_last(node **head, int data) {
    // 리스트가 비어있을 경우 head에 input
    if (*head == NULL) {
        (*head)->data = data;
        (*head)->next = NULL;
        return;
    }
    // 제일 마지막 노드에 도착
    if ((*head)->next == NULL) {
        // 새로운 노드 생성
        node *temp = (node *) malloc(sizeof(node));
        // 노드에 data, next 설정
        temp->data = data;
        temp->next = NULL;
        // 마지막 노드 next에 temp 노드 추가
        (*head)->next = temp;
        return;
    }
    // 재귀함수
    insert_last(&(*head)->next, data);
}

// 찾기 함수
int search(node **head, int data) {
    // 인덱스는 0번 부터 싲가
    int idx = 0;
    // head 값 temp에 복사해서 값을 찾으면 idx 반환한다.
    for (node *temp = *head; temp != NULL; temp = temp->next, ++idx) {
        if (temp->data == data) {
            return idx;
        }
    }
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
    node *temp = *head;
    *head = (*head)->next;
    // head 노드의 데이터 저장
    int del = temp->data;

    free(temp);
    return del;
}

// data와 일치하는 node 삭제
int delete_(node **head, int data) {
    int del;
    // 리스트가 비었으면 -1 반환
    if (*head == NULL) {
        return -1;
    }
    // 임시 노드 생성
    node *temp;
    // 현재 노드의 data가 매개변수 data와 동일할 때
    if ((*head)->data == data) {
        temp = *head;
        *head = (*head)->next;
        del = temp->data;
        free(temp);
        return del;
    }
    // 현재 노드 head를 prev노드에 복사한다.다음노드가 data와 같으면 삭제한다.
    for (node *prev = *head; prev->next != NULL; prev = prev->next) {
        if (prev->next->data == data) {
            temp = prev->next;
            prev->next = temp->next;
            del = temp->data;
            free(temp);
            return del;
        }
    }
    // 삭제 못하면 -1 반환
    return -1;
}

// 역순 시킨다.
void invert(node **head) {

    node *q = NULL, *r;
    // *head가 NULL이 될때 까지 반복한다.
    while (*head) {
        r = q;
        q = *head;
        *head = (*head)->next;
        q->next = r;
    }
    // *head가 q를 가리키게 한다.
    *head = q;
}

// 링크드 리스트 정렬 함수
void lsort(node **head) {
    // *head가 NULL이면 끝냄
    if (*head == NULL) {
        return;
    }
    // 선택 정렬을 하는데 노드를 바꾸는게 아니라 data만 바꾼다.
    for(node *i = *head; i->next!=NULL; i = i->next) {
        for (node *j = i->next; j!= NULL; j = j->next) {
            if (cmp(i->data, j->data)) {
                int temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
}

// 병합 해주는 함수
node *merge(node **a, node **b) {
    // 병합되는 노드의 첫번째를 가리킨다.
    node *s;
    // 노드의 끝을 가리킨다.
    node *e;

    // a노드의 data가 b노드의 data보다 작으면 s = *a input, 아니면 *b 인풋
    if (!cmp((*a)->data, (*b)->data)) {
        s = *a;
        e = s;
        *a = (*a)->next;
    } else {
        s = *b;
        e = s;
        *b = (*b)->next;
    }

    // *a, *b가 모두 NULL 일때 까지 반복한다.
    while (*a || *b) {
        // *a 가 NULL이고 *b가 NULL이 아닐 때
        if (!*a && *b) {
            e->next = *b;
            e = e->next;
            *b = (*b)->next;
            continue;
        }
        // *a가 NULL이 아니고 *b가 NULL일 때
        if (*a && !*b) {
            e->next = *a;
            e = e->next;
            *a = (*a)->next;
            continue;
        }
        // *a, *b 둘다 NULL이 아닐 때, *a < *b일 때
        if (!cmp((*a)->data, (*b)->data)) {
            e->next = *a;
            e = e->next;
            *a = (*a)->next;
        } else {
            e->next = *b;
            e = e->next;
            *b = (*b)->next;
        }
    }

    return s;
}