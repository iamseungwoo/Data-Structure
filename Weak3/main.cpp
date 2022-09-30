#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct polynomial {
    int exponenet;     // 지수
    float coefficient; // 계수
};

int termCntArr[] = { 0, 0, 0 };

void draw(polynomial* P, int n) {
    for (int i = 0; i < n; i++) {
        printf("%8.3f %8d\n", P[i].coefficient, P[i].exponenet);
    }
}

int cmp(const void* A, const void* B) {
    if (((polynomial*)A)->exponenet < ((polynomial*)B)->exponenet) {
        return 1;
    }
    else if (((polynomial*)A)->exponenet > ((polynomial*)B)->exponenet) {
        return -1;
    }
    else {
        return 0;
    }
}


polynomial* padd(polynomial* A, polynomial* B) {
    polynomial* temp = (polynomial*)malloc(sizeof(polynomial) * (termCntArr[0] + termCntArr[1]));
    int aTerm = 0;
    int bTerm = 0;
    int tempTerm = 0;
    while (1) {
        if (aTerm == termCntArr[0] && bTerm == termCntArr[1]) {
            break;
        }
        if (A[aTerm].exponenet > B[bTerm].exponenet) {
            temp[tempTerm].exponenet = A[aTerm].exponenet;
            temp[tempTerm++].coefficient = A[aTerm++].coefficient;


        }
        else if (A[aTerm].exponenet < B[bTerm].exponenet) {
            temp[tempTerm].exponenet = B[bTerm].exponenet;
            temp[tempTerm++].coefficient = B[bTerm++].coefficient;


        }
        else if (A[aTerm].exponenet == B[bTerm].exponenet) {
            temp[tempTerm].exponenet = A[aTerm].exponenet;
            temp[tempTerm++].coefficient = A[aTerm++].coefficient + B[bTerm++].coefficient;

        }
    }
    termCntArr[2] = tempTerm;
    temp = (polynomial*)realloc(temp, sizeof(polynomial) * tempTerm);
    return temp;
}

polynomial* pmul(polynomial* A, polynomial* B) {
    int cycle = termCntArr[0];
    termCntArr[0] = 0;
    polynomial* D = (polynomial*)malloc(sizeof(polynomial)*0);
    for (int i = 0; i < cycle; i++) {
        polynomial* Ci = (polynomial*)malloc(sizeof(polynomial) * termCntArr[1]);
        for (int j = 0; j < termCntArr[1]; j++) {
            Ci[j].exponenet = A[i].exponenet + B[j].exponenet;
            Ci[j].coefficient = A[i].coefficient * B[j].coefficient;
        }
        printf("C%d(x)\n", i + 1);
        draw(Ci, termCntArr[1]);
        D = padd(D, Ci);
        termCntArr[0] = termCntArr[2];
    }
    return D;
}


int main() {
    int initSize[] = { 10, 10 };
    polynomial* A = (polynomial*)malloc(sizeof(polynomial) * initSize[0]);
    polynomial* B = (polynomial*)malloc(sizeof(polynomial) * initSize[1]);

    while (1) {

        int tempExpo;   // 지수
        float tempCoef; // 계수
        printf("A(x)의 항을 입력하세요. (coef expon) : ");
        scanf("%f %d", &tempCoef, &tempExpo);

        if (tempExpo == -1) {
            break; // -1 입력시 종료
        }

        if (termCntArr[0] == 9) {
            A = (polynomial*)realloc(A, sizeof(polynomial) * initSize[0] * 2);
            initSize[0] *= 2;
        }
        A[termCntArr[0]].exponenet = tempExpo;
        A[termCntArr[0]].coefficient = tempCoef;
        termCntArr[0] += 1;
    }
    qsort((polynomial*)A, termCntArr[0], sizeof(polynomial), cmp);

    printf("다항식 A(x)\n");
    printf("    coef    expon\n");
    for (int i = 0; i < termCntArr[0]; i++) {
        printf("%8.3f %8d\n", A[i].coefficient, A[i].exponenet);
    }

    while (1) {

        int tempExpo;   // 지수
        float tempCoef; // 계수
        printf("B(x)의 항을 입력하세요. (coef expon) : ");
        scanf("%f %d", &tempCoef, &tempExpo);

        if (tempExpo == -1) {
            break; // -1 입력시 종료
        }

        if (termCntArr[1] == 9) {
            B = (polynomial*)realloc(B, sizeof(polynomial) * initSize[1] * 2);
            initSize[1] *= 2;
        }
        B[termCntArr[1]].exponenet = tempExpo;
        B[termCntArr[1]].coefficient = tempCoef;
        termCntArr[1] += 1;
    }
    qsort((polynomial*)B, termCntArr[1], sizeof(polynomial), cmp);

    printf("다항식 B(x)\n");
    printf("    coef    expon\n");
    for (int i = 0; i < termCntArr[1]; i++) {
        printf("%8.3f %8d\n", B[i].coefficient, B[i].exponenet);
    }

    polynomial* D = padd(A, B);

    printf("3.2 다항식 덧셈\n다항식 덧셈 결과 : D(x)\n");
    printf("    coef    expon\n");
    for (int i = 0; i < termCntArr[2]; i++) {
        printf("%8.3f %8d\n", D[i].coefficient, D[i].exponenet);
    }

    D = pmul(A, B);
    printf("D(x) 곱셈\n");
    draw(D, termCntArr[0]);
}