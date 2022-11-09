#include <stdio.h>
#include <cstdlib>
#include "Polynomial.h"

polyPointer avail;

// a, b 지수 비교 함수 a가 더크면 1, b가 더크면 -1, a=b이면 0 return
int compare(int aExpon, int bExpon) {
    if (aExpon < bExpon) {
        return -1;
    } else if (aExpon > bExpon) {
        return 1;
    } else {
        return 0;
    }
}

// 가용 리스트가 있으면 가져오고 없으면 새로 동적할당
polyPointer create_polynomial() {
    polyPointer node = getNode();
    // 지수를 -1 로 만들어 헤드 node로 만들어줌
    node->expon = -1;
    // circular linked list
    node->link = node;
    return node;
}

// add func
polyPointer cpadd(polyPointer a, polyPointer b) {
    // a, b head node
    polyPointer startA, startB;
    // c head node, rear nnode
    polyPointer front, rear;

    startA = a;
    startB = b;
    // 실제 값이 있는 노드로 옮김 expon이 -1 에서 -1이 아닌 것으로
    a = a->link;
    b = b->link;

    // node 생성
    front = create_polynomial();
    rear = front;

    int sum, doneA = 0, doneB = 0;
    do {
        switch (compare(a->expon, b->expon)) {
            case -1:
                attach(b->coef, b->expon, &rear);
                b = b->link;
                break;
            case 0:
                // (a,b) 둘중 하나끝나거나, (a,b) 둘다 끝났을 때 걸린다. a, b 둘다 head 노드로 돌아오기 때문에 a = b 일 때만 조건문 해도됨
                if (startA == a) {
                    doneA = 1;
                }
                if (startB == b) {
                    doneB = 1;
                }

                sum = (int) (a->coef + b->coef);
                if (sum) {
                    attach((float) sum, a->expon, &rear);
                }
                a = a->link;
                b = b->link;
                break;
            case 1:
                attach(a->coef, a->expon, &rear);
                a = a->link;
        }
    } while (!doneA && !doneB);

    // a는 안끝나고 b는 끝났을 때
    if (doneB && !doneA) {
        for (; !doneA; a = a->link) {
            if (a == startA) {
                doneA = 1;
            }
            attach(a->coef, a->expon, &rear);
        }
    }

    // b는 안끝나고 a는 끝났을 때
    if (doneA && !doneB) {
        for (; !doneB; b = b->link) {
            if (b == startB) {
                doneB = 1;
            }
            attach(b->coef, b->expon, &rear);
        }
    }
    // attach에서 rear->link 는 front 되게 설정됨
    return front;
}

// rear 뒤에 삽입
void attach(float coefficient, int exponent, polyPointer *rear) {
    // 노드 생성
    polyPointer temp;
    temp = getNode();
    if (temp == NULL) {
        fprintf(stderr, "memory is full\n");
        exit(1);
    }
    temp->coef = coefficient;
    temp->expon = exponent;
    // temp->link 는 rear->link 해서 원형 리스트 유지 해줌
    temp->link = (*rear)->link;
    (*rear)->link = temp;
    *rear = temp;
}

// 해당 포인터를 avail 앞에다가 넣어주고, NULL 시켜줌 통째로 free 해주는 느낌
void cerase(polyPointer *ptr) {
    polyPointer temp;
    if (*ptr) {
        temp = (*ptr)->link;
        (*ptr)->link = avail;
        avail = temp;
        *ptr = NULL;
    }
}
// 가용 리스트 있으면 반환 하고 아니면 새로 동적할당 해준다.
polyPointer getNode(void) {
    polyPointer node;
    if (avail != NULL) {
        node = avail;
        avail = avail->link;
    } else {
        node = (polyPointer) malloc(sizeof(polyNode));
        if (node == NULL) {
            fprintf(stderr, "memory full\n");
            exit(1);
        }
    }
    return node;
}
// 해당 노드를 avail 앞에다가 붙여줌, avail에 하나 추가하는 느낌
void retNode(polyPointer ptr) {
    ptr->link = avail;
    avail = ptr;
}

// head 노드로 돌아오면 끝남, 원형리스트 출력함수
void print_polynomial(polyPointer C) {
    printf("    coef    expon\n");
    C = C->link;
    while (C->expon != -1) {
        printf("%8.2f%9d\n", C->coef, C->expon);
        C = C->link;
    }
}

// 단일 곱셈
polyPointer single_cpmul(polyNode Ai, polyPointer B) {
    polyPointer Ci = create_polynomial();
    B = B->link;
    // print_polynomial 과 같이 head노드로 돌아오면 끝남
    while (B->expon != -1) {
        attach(Ai.coef * B->coef, Ai.expon + B->expon, &Ci);
        B = B->link;
    }
    // Ci rear에서 head노드로 바꿔줌
    Ci = Ci->link;
    return Ci;
}

// 전체 곱셈 함수
polyPointer cpmul(polyPointer A, polyPointer B) {
    // 곱셈 다항식 D 생성
    polyPointer D;
    // D항의 개수
    int dFlag = 0;
    // Ai는 head노드가 아닌 그다음 노드부터 시작. 다시 head노드 즉 expon이 -1면 escape, Ai = Ai->link해준다.
    for (polyPointer Ai = A->link; Ai->expon != -1; Ai = Ai->link) {
        // 단일 곱셈 결과
        polyPointer Ci = single_cpmul(*Ai, B);
        // Ci 출력
        printf("singul_mul - C%d(x)\n", dFlag + 1);
        print_polynomial(Ci);
        // 처음 곱셈하면 D에 그대로 Ci 복사해줌
        if (!dFlag) {
            D = Ci;
        } else{
            // 두번째 곱셈 부터 D 와 Ci 더해준다.
            D = cpadd(D, Ci);
        }
        // 항 증가.
        dFlag++;
    }
    return D;
}

// 정렬함수 node 자체가 바뀌는게 아닌 expon, coef 만 교환해준다. 선택정렬 사용
void lsot(polyPointer *rear) {
    for (polyPointer i = *rear; i->link->expon != -1; i = i->link) {
        for (polyPointer j = i->link; j->expon != -1; j = j->link) {
            // i->expon이 j->expon보다 작으면 교환함
            if (compare(i->expon, j->expon) == -1) {
                int tempCoef = i->coef;
                int tempExpon = i->expon;
                i->coef = j->coef;
                i->expon = j->expon;
                j->coef = tempCoef;
                j->expon = tempExpon;
            }
        }
    }
}

int main() {
    printf("7.1. 다항식 생성\n"
           "다항식 A(x)\n");
    polyPointer A = create_polynomial();
    // coef, expon 입력 변수
    float coef;
    int expon;
    while (1) {
        printf("다항식의 항을 입력하세요. (coef expon) : ");
        scanf("%f %d", &coef, &expon);
        if (expon == -1) break;
        attach(coef, expon, &A);
    }
    // A가 head노드를 가리키게 하기 위해서
    A = A->link;
    // A리스트 정렬
    lsot(&(A->link));
    // A 리스트 출력
    print_polynomial(A);


    // A 리스트와 내용 같음.
    printf("다항식 B(x)\n");
    polyPointer B = create_polynomial();
    while (1) {
        printf("다항식의 항을 입력하세요. (coef expon) : ");
        scanf("%f %d", &coef, &expon);
        if (expon == -1) break;
        attach(coef, expon, &B);
    }
    B = B->link;
    lsot(&(B->link));
    print_polynomial(B);

    printf("7.2 다항식 덧셈\n"
           "다항식 덧셈 결과 : D(x)\n");
    polyPointer C = cpadd(A, B);
    print_polynomial(C);
    // C 안쓰니깐 가용 리스트로 넘김
    cerase(&C);


    printf("7.3 다항식 곱셈\n");
    polyPointer D = cpmul(A, B);
    printf("다항식 곱셈 결과 : D(x)\n");
    print_polynomial(D);
    // D 안쓰니깐 가용 리스트로 넘김
    cerase(&D);

    // A, B 안쓰니깐 넘기기
    cerase(&A);
    cerase(&B);
    return 0;
}
