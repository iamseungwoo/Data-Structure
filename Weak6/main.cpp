#include <stdio.h>
#include "Linked.h"
#include "Stack.h"
#include "Queue.h"

int main() {
    // 연결리스트 head는 NULL로 초기화
    node *head = NULL;
    int choice; // 메뉴 선택
    int data;   // push, addq등 입력 데이터
    int del;    // 삭제 데이터
    int idx;    // search로 반환하는 index
    while (1) {
        // 메뉴 선택
        printf("\n리스트 기본연산\n0. print list\n1. insert_front\n2. insert_last\n3. delete_front\n4. delete_\n5. search\n6. invert\n-1. exit\n");
        printf("어떤 기능을 수행할까요? : ");
        scanf("%d", &choice);
        if (choice == -1) {
            printf("Bye-bye~\n");
            break;
        }
        // 연결리스트 출력
        if (choice == 0) {
            print_list(head);
        }
        // 데이터 맨앞 추가
        if (choice == 1) {
            printf("데이터 ");
            scanf("%d", &data);
            insert_front(&head, data);
        }
        // 데이터 맨뒤 추가
        if (choice == 2) {
            printf("데이터 ");
            scanf("%d", &data);
            insert_last(&head, data);
        }
        // 데이터 맨앞 삭제
        if (choice == 3) {
            del = delete_front(&head);
            printf("삭제 데이터 : %d\n", del);
        }
        // 데이터 맨뒤 삭제
        if (choice == 4) {
            printf("데이터 ");
            scanf("%d", &data);
            del = delete_(&head, data);
            printf("삭제 데이터 : %d\n", del);
        }
        // 데이터 검색, index 리턴
        if (choice == 5) {
            printf("데이터 ");
            scanf("%d", &data);
            idx = search(&head, data);
            printf("노드번호 : %d\n", idx);
        }
        // 추가연산 invert 함수 구현
        if (choice == 6) {
            invert(&head);
        }
        printf("리스트 : ");
        print_list(head);
    }
    // 링크드 리스트 기반 스택 생성
    stack st;
    // top = NULL로 초기화
    StackInit(&st);

    while (1) {
        printf(" 리스트로 구현한 스택\n"
               " 1. push\n"
               " 2. pop\n"
               "-1. exit\n");
        printf("어떤 기능을 수행할까요? : ");
        scanf("%d", &choice);
        // 끝내기
        if (choice == -1) {
            break;
        }
        // push
        if (choice == 1) {
            printf("push item :");
            scanf("%d", &data);
            SPush(&st, data);
        }
        // pop
        if (choice == 2) {
            printf("pop item :%d\n", SPop(&st));
        }
        print_stack(st);
    }
    // 큐 생성
    queue qu;
    initQ(&qu);

    while (1) {
        printf(" 리스트로 구현한 큐\n"
               " 1. addq\n"
               " 2. deleteq\n"
               "-1. exit\n"
               "어떤 기능을 수행할까요? : ");
        scanf("%d", &choice);

        if (choice == -1) {
            break;
        }
        if (choice == 1) {
            printf("addq item :");
            scanf("%d", &data);
            addQ(&qu, data);
        }
        if (choice == 2) {
            printf("deleteq item: %d\n", deleteQ(&qu));
        }
        print_queue(qu);
    }

    printf("\n-----------\n");
    printf("merge 함수 구현");
    node *a = NULL;
    node *b = NULL;
    while (1) {
        printf("a 입력 데이터 : ");
        scanf("%d", &data);
        if (data == -1) {
            break;
        }
        insert_front(&a, data);
    }
    lsort(&a);
    while (1) {
        printf("b 입력 데이터 : ");
        scanf("%d", &data);
        if (data == -1) {
            break;
        }
        insert_front(&b, data);
    }
    lsort(&b);
    node * d = merge(&a, &b);
    print_list(d);
    return 0;
}
