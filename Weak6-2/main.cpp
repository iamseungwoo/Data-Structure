#include <stdio.h>
#include "CircluarLinked.h"
#include "Stack.h"
#include "Queue.h"

int main() {
    // 원형연결리스트 head는 NULL로 초기화
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
            idx = search(head, data);
            printf("노드번호 : %d\n", idx);
        }
        // 추가연산 invert 함수 구현
        if (choice == 6) {
            invert(&head);
        }
        printf("리스트 : ");
        print_list(head);
    }
    return 0;
}
