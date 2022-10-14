#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// 스택 구조체 생성
typedef struct _Stack {
private:
    // 스택 배열 동적할당
    int *arr = (int *) malloc(sizeof(int) * 10);
    int top = -1;
    // 기본사이즈
    int size = 10;
public:
    // 구조체 함수들
    void push(int item);

    int pop();

    void draw();
} Stack;

// stack push 구현
void Stack::push(int item) {
    // 꽉찼을 때
    if (top == size - 1) {
        // 비트연산, 사이즈 두배
        size = size << 1;
        // 재할당
        arr = (int *) realloc(arr, sizeof(int) * size);
    }
    arr[++top] = item;
}

int Stack::pop() {
    // 비엇을 때
    if (top == -1) {
        printf("empty!\n");
        return -1;
    }
    return arr[top--];
}

// 현재 스택에 들어있는 요소 출력
void Stack::draw() {
    printf(" index : item\n");
    for (int i = 0; i <= top; i++) {
        printf("     %d :  %d\n", i, arr[i]);
    }
}

// 큐 구조체 생성
typedef struct _Queue {
private:
    // 동적할당
    int *arr = (int *) malloc(sizeof(int) * 10);
    int size = 10;
    int front = 0;
    int rear = 0;
public:
    int pop();

    void push(int item);

    void draw();
} Queue;

void Queue::push(int item) {
    // 큐가 꽉찼을 때
    if (rear == size) {
        printf("is full!\n");
        // 새로운 동작할당 배열 만듦
        int *temp = (int *) malloc(sizeof(int) * size);
        int i;
        // arr 의 front 부터 rear 까지 temp 배열에 할당
        for (i = 0; i + front <= rear; i++) {
            temp[i] = arr[front + i];
        }
        // arr에 temp 값 넣음
        arr = temp;
        // front 는 0
        front = 0;
        // rear 도 i-1
        rear = i - 1;
        memcpy(arr, temp, sizeof(int)*size);9
        // size 두배
        size = size << 1;
        // 두배 사이즈 재할당
        arr = (int *) realloc(arr, sizeof(int) * size);
        // 동적할당 해제
        free(temp);
    }
    arr[rear++] = item;
}

int Queue::pop() {
    if (front == rear) {
        printf("is empty!");
        return -1;
    }
    return arr[front++];
}

// 큐 안의 아이템 보여줌
void Queue::draw() {
    printf(" index : item\n");
    // front ~ rear-1 까지 출력
    for (int i = 0; i + front < rear; i++) {
        printf("     %d :  %d\n", i, arr[i + front]);
    }
}

typedef struct _CircleQ {
private:
    // 원형큐 배열 동적할당
    int *arr = (int *) malloc(sizeof(int) * 10);
    int rear = 4;
    int front = 4;
    int size = 10;
public:
    void push(int item);

    int pop();

    void draw();
} CircleQ;

void CircleQ::push(int item) {
    // rear가 다음이 front면 꽉찬걸로 한다
    if ((rear + 1) % size == front) {
        printf("is Full!\n");
        // 임시배열 동적할당
        int *temp = (int *) malloc(sizeof(int) * size);
        int i;
        // front 부터 rear까지 temp에 값 복사
        for (i = 0; front != rear; i++) {
            temp[i] = arr[front++];
            front %= size;
        }
        front = 0;
        rear = i;
        memcpy(arr, temp, sizeof(int)*size);
        // 사이즈 두배
        size = size << 1;
        free(temp);
        // 재할당
        arr = (int *) realloc(arr, sizeof(int) * size);
    }
    arr[rear] = item;
    rear = (rear + 1) % size;
}

int CircleQ::pop() {
    // front == rear 이면 비었음
    if (front == rear) {
        printf("is empty!\n");
        return -1;
    }
    return arr[front++];
}

void CircleQ::draw() {
    printf(" index : item\n");
    // front 부터 rear-1 까지 출력
    for (int i = front; i % size != rear; i++ ) {
        i %= size;
        printf("     %d :  %d\n", i, arr[i]);
    }
}

int main() {
    Stack st;
    Queue qu;
    CircleQ cq;

    printf("4.1. 스택\n");
    while (1) {
        printf("스택 - 1.push 2.pop : ");
        int choice;
        scanf("%d", &choice);
        if (choice == -1) {
            break;
        }
        switch (choice) {
            case 1:
                printf("push item : ");
                int item;
                scanf("%d", &item);
                st.push(item);
                st.draw();
                break;
            case 2:
                printf("pop item : %d\n", st.pop());
                st.draw();
                break;
        }
    }
    printf("4.2. 선형큐\n");
    while (1) {
        printf("선형큐 - 1.push 2.pop : ");
        int choice;
        scanf("%d", &choice);
        if (choice == -1) {
            break;
        }
        switch (choice) {
            case 1:
                printf("push item : ");
                int item;
                scanf("%d", &item);
                qu.push(item);
                qu.draw();
                break;
            case 2:
                printf("pop item : %d\n", qu.pop());
                qu.draw();
                break;
        }
    }
    printf("4.3. 원형큐\n");
    while (1) {
        printf("원형큐 - 1.push 2.pop : ");
        int choice;
        scanf("%d", &choice);
        if (choice == -1) {
            break;
        }
        switch (choice) {
            case 1:
                printf("push item : ");
                int item;
                scanf("%d", &item);
                cq.push(item);
                cq.draw();
                break;
            case 2:
                printf("pop item : %d\n", cq.pop());
                cq.draw();
                break;
        }
    }

    return 0;
}
