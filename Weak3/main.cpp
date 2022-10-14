//#define _CRT_SECURE_NO_WARNINGS
//
//#include <stdio.h>
//#include <stdlib.h>
//
//struct polynomial {
//    int exponenet;     // 지수
//    float coefficient; // 계수
//};
//
//int termCntArr[] = {0, 0, 0};
//
//void draw(polynomial *P, int n) {
//    for (int i = 0; i < n; i++) {
//        printf("%8.3f %8d\n", P[i].coefficient, P[i].exponenet);
//    }
//}
//
//int cmp(const void *A, const void *B) {
//    if (((polynomial *)A)->exponenet < ((polynomial *)B)->exponenet) {
//        return 1;
//    } else if (((polynomial *)A)->exponenet > ((polynomial *)B)->exponenet) {
//        return -1;
//    } else {
//        return 0;
//    }
//}
//
//polynomial *padd(polynomial *A, polynomial *B) {
//    polynomial *temp = (polynomial *)malloc(sizeof(polynomial) * (termCntArr[0] + termCntArr[1]));
//    int aTerm = 0;
//    int bTerm = 0;
//    int tempTerm = 0;
//
//    while (1) {
//        if (aTerm >= termCntArr[0] && bTerm >= termCntArr[1]) {
//            break;
//        }
//        if (A[aTerm].exponenet > B[bTerm].exponenet) {
//            temp[tempTerm].exponenet = A[aTerm].exponenet;
//            temp[tempTerm++].coefficient = A[aTerm++].coefficient;
//            continue;
//        } else if (A[aTerm].exponenet < B[bTerm].exponenet) {
//            temp[tempTerm].exponenet = B[bTerm].exponenet;
//            temp[tempTerm++].coefficient = B[bTerm++].coefficient;
//            continue;
//        } else if (A[aTerm].exponenet == B[bTerm].exponenet) {
//            temp[tempTerm].exponenet = A[aTerm].exponenet;
//            temp[tempTerm++].coefficient = A[aTerm++].coefficient + B[bTerm++].coefficient;
//            continue;
//        }
//    }
//    termCntArr[2] = tempTerm;
//    return temp;
//}
//
//polynomial *pmul(polynomial *A, polynomial *B) {
//    int cycle = termCntArr[0];
//    termCntArr[0] = 0;
//    polynomial *D = (polynomial *)malloc(sizeof(polynomial) * 0);
//    for (int i = 0; i < cycle; i++) {
//        polynomial *Ci = (polynomial *)malloc(sizeof(polynomial) * termCntArr[1]);
//        for (int j = 0; j < termCntArr[1]; j++) {
//            Ci[j].exponenet = A[i].exponenet + B[j].exponenet;
//            Ci[j].coefficient = A[i].coefficient * B[j].coefficient;
//        }
//        printf("C%d(x)\n", i + 1);
//        draw(Ci, termCntArr[1]);
//        D = padd(D, Ci);
//        D = (polynomial *)realloc(D, (sizeof(polynomial) * termCntArr[2]));
//        termCntArr[0] = termCntArr[2];
//        free(Ci);
//    }
//
//    return D;
//}
//
//int main() {
//    int initSize[] = {10, 10};
//    polynomial *A = (polynomial *)malloc(sizeof(polynomial) * initSize[0]);
//    polynomial *B = (polynomial *)malloc(sizeof(polynomial) * initSize[1]);
//
//    while (1) {
//
//        int tempExpo;   // 지수
//        float tempCoef; // 계수
//        printf("A(x)의 항을 입력하세요. (coef expon) : ");
//        scanf("%f %d", &tempCoef, &tempExpo);
//
//        if (tempExpo == -1) {
//            break; // -1 입력시 종료
//        }
//
//        if (termCntArr[0] == initSize[0] - 1) {
//            initSize[0] *= 2;
//            A = (polynomial *)realloc(A, sizeof(polynomial) * initSize[0]);
//        }
//        A[termCntArr[0]].exponenet = tempExpo;
//        A[termCntArr[0]].coefficient = tempCoef;
//        termCntArr[0] += 1;
//    }
//    qsort((polynomial *)A, termCntArr[0], sizeof(polynomial), cmp);
//
//    printf("다항식 A(x)\n");
//    printf("    coef    expon\n");
//    for (int i = 0; i < termCntArr[0]; i++) {
//        printf("%8.3f %8d\n", A[i].coefficient, A[i].exponenet);
//    }
//
//    while (1) {
//
//        int tempExpo;   // 지수
//        float tempCoef; // 계수
//        printf("B(x)의 항을 입력하세요. (coef expon) : ");
//        scanf("%f %d", &tempCoef, &tempExpo);
//
//        if (tempExpo == -1) {
//            break; // -1 입력시 종료
//        }
//
//        if (termCntArr[1] == initSize[1] - 1) {
//            initSize[1] *= 2;
//            B = (polynomial *)realloc(B, sizeof(polynomial) * initSize[1]);
//        }
//        B[termCntArr[1]].exponenet = tempExpo;
//        B[termCntArr[1]].coefficient = tempCoef;
//        termCntArr[1] += 1;
//    }
//    qsort((polynomial *)B, termCntArr[1], sizeof(polynomial), cmp);
//
//    printf("다항식 B(x)\n");
//    printf("    coef    expon\n");
//    for (int i = 0; i < termCntArr[1]; i++) {
//        printf("%8.3f %8d\n", B[i].coefficient, B[i].exponenet);
//    }
//
//    polynomial *D;
//    D = padd(A, B);
//    printf("3.2 다항식 덧셈\n다항식 덧셈 결과 : D(x)\n");
//    printf("    coef    expon\n");
//    draw(D, termCntArr[2]);
//
//    D = pmul(A, B);
//    printf("D(x) 곱셈\n");
//    draw(D, termCntArr[2]);
//}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct polynomial {
    int exponenet;     // 지수
    float coefficient; // 계수
};

// 현재 다항식 항의 개수, 0번째 인덱스는 A, 1번째 인덱스는 B, 2번째 인덱스는 A+B한 다항식의 항의개수
int termCntArr[] = {0, 0, 0};

// 다항식 출력 함수
void draw(polynomial *P, int n) {
    for (int i = 0; i < n; i++) {
        printf("%8.3f %8d\n", P[i].coefficient, P[i].exponenet);
    }
}

// 값 비교 함수 퀵정렬 함수 정렬, 내림차순 비교.
int cmp(const void *A, const void *B) {
    if (((polynomial *)A)->exponenet < ((polynomial *)B)->exponenet) {
        return 1;
    } else if (((polynomial *)A)->exponenet > ((polynomial *)B)->exponenet) {
        return -1;
    } else {
        return 0;
    }
}

// 다항식 더하기 함수
polynomial *padd(polynomial *A, polynomial *B) {
    // 임시로 더하기 한 값을 저장하는 다항식
    polynomial *temp = (polynomial *)malloc(sizeof(polynomial) * (termCntArr[0] + termCntArr[1]));
    // A 의 인덱스
    int aTerm = 0;
    // B의 인덱스
    int bTerm = 0;
    // Temp의 인덱스
    int tempTerm = 0;

    while (1) {
        // A인덱스와 B인덱스가 항의 개수 이상일 때 탈출, 부등식이 == 이 아니라 >= 으로 하는 이유는
        //아래에서 aTerm이나 bTerm 둘중 하나가 termCntArr[i]가되면 다항식이 저장된 값을 넘어 0,0 을 가리키기 때문에
        //  만약 aTerm이 termCntArr[0]이되면 다음 반복문에서, A의 지수와 계수가 0, 0 이고 다른 한 다항식의(B) 마지막
        //  지수가 0이면
        // B식의 지수가 더크게 되는 것이 아니라 A식의 지수와 같다고 판정하기 때문에 aTerm이 부득이하게
        // termCntArr[0]이상이 된다. 오버 플로우가 일어나지는 않음 애초에 동적할당한 다항식들은 실제 항의 개수보다 크게
        // 사이즈를 줬기 때문에
        if (aTerm >= termCntArr[0] && bTerm >= termCntArr[1]) {
            break;
        }
        // A지수가 클 때 임시 다항식에 지수과 계수를 넣어주고 인덱스를 +1 해줌
        if (A[aTerm].exponenet > B[bTerm].exponenet) {
            temp[tempTerm].exponenet = A[aTerm].exponenet;
            temp[tempTerm++].coefficient = A[aTerm++].coefficient;
            continue;
        }
            // B지수가 클 때 임시 다항식에 지수와 계수를 넣어주고 인데스를 +1 해줌
        else if (A[aTerm].exponenet < B[bTerm].exponenet) {
            temp[tempTerm].exponenet = B[bTerm].exponenet;
            temp[tempTerm++].coefficient = B[bTerm++].coefficient;
            continue;
        }
            // A지수와 B 지수가 같을 때.
        else if (A[aTerm].exponenet == B[bTerm].exponenet) {
            temp[tempTerm].exponenet = A[aTerm].exponenet;
            temp[tempTerm++].coefficient = A[aTerm++].coefficient + B[bTerm++].coefficient;
            continue;
        }
    }
    // A+B의 항의 개수 tempTerm을 업데이트 해줌
    termCntArr[2] = tempTerm;
    // 더한 다항식 반환
    return temp;
}

// 다항식 곱셈 함수
polynomial *pmul(polynomial *A, polynomial *B) {
    // A항의 개수만큼 곱하므로 cycle 변수에 넣어줌
    int cycle = termCntArr[0];
    // 곱한후 더할 때 format은 D = padd(D,Ci) 이므로 처음 D의 항의 개수는 0으로해줌. D + Ci 형태이므로 D가
    // termCntArr[0], Ci가 termCntArr[1]의 항의 개수를 가짐.
    termCntArr[0] = 0;
    // 다항식 D 동적할당
    polynomial *D = (polynomial *)malloc(sizeof(polynomial) * 0);

    for (int i = 0; i < cycle; i++) {
        // A[i] * B를 곱해서 저장할 Ci 다항식 동적 할당
        polynomial *Ci = (polynomial *)malloc(sizeof(polynomial) * termCntArr[1]);
        // 곱해지는 B는 항이 termCntArr[1] 개 만큼 있으므로 반복문
        for (int j = 0; j < termCntArr[1]; j++) {
            Ci[j].exponenet = A[i].exponenet + B[j].exponenet;
            Ci[j].coefficient = A[i].coefficient * B[j].coefficient;
        }
        printf("singul_mul - C%d(x)\n", i + 1);
        // 곱해진 Ci 값 출력
        draw(Ci, termCntArr[1]);
        // 곱해진 값 더하기
        D = padd(D, Ci);
        // D = D + Ci 이기 때문에 더해질 D의 항의개수 업데이트
        termCntArr[0] = termCntArr[2];
        // 동적할당한 Ci 해제
        free(Ci);
        D = (polynomial *)realloc(D, (sizeof(polynomial) * termCntArr[2]));
    }
    // 곱셈결과 반환
    return D;
}

int main() {
    // 초기 다항식 사이즈, 0번째 인덱스는 A, 1번째 인덱스는 B
    int initSize[] = {10, 10};
    polynomial *A = (polynomial *)malloc(sizeof(polynomial) * initSize[0]);
    polynomial *B = (polynomial *)malloc(sizeof(polynomial) * initSize[1]);

    printf("3.1. 다항식 생성\n");
    while (1) {

        int tempExpo;   // 지수
        float tempCoef; // 계수
        printf("A(x)의 항을 입력하세요. (coef expon) : ");
        scanf("%f %d", &tempCoef, &tempExpo);

        if (tempExpo == -1) {
            break; // 지수 -1 입력시 종료
        }

        // 입력된 항이 size가 되면 원래 사이즈 두배만큼 재할당, 사이즈 값 두배해줌
        if (termCntArr[0] == initSize[0] - 1) {
            A = (polynomial *)realloc(A, sizeof(polynomial) * initSize[0] * 2);
            initSize[0] *= 2;
        }

        // 값넣기
        A[termCntArr[0]].exponenet = tempExpo;
        A[termCntArr[0]].coefficient = tempCoef;
        // 항의 개수 +1 카운팅
        termCntArr[0] += 1;
    }
    // stdlib.h 파일에 들어있는 퀵정렬함수
    qsort((polynomial *)A, termCntArr[0], sizeof(polynomial), cmp);

    // 다항식 A 출력
    printf("다항식 A(x)\n");
    printf("    coef    expon\n");
    draw(A, termCntArr[0]);

    // 위의 다항식 A와 같은 로직
    while (1) {

        int tempExpo;   // 지수
        float tempCoef; // 계수
        printf("B(x)의 항을 입력하세요. (coef expon) : ");
        scanf("%f %d", &tempCoef, &tempExpo);

        if (tempExpo == -1) {
            break; // -1 입력시 종료
        }

        if (termCntArr[1] == initSize[1] - 1) {
            B = (polynomial *)realloc(B, sizeof(polynomial) * initSize[1] * 2);
            initSize[1] *= 2;
        }
        B[termCntArr[1]].exponenet = tempExpo;
        B[termCntArr[1]].coefficient = tempCoef;
        termCntArr[1] += 1;
    }
    ㅡ((polynomial *)B, termCntArr[1], sizeof(polynomial), cmp);

    // 다항식 B출력
    printf("다항식 B(x)\n");
    printf("    coef    expon\n");
    for (int i = 0; i < termCntArr[1]; i++) {
        printf("%8.3f %8d\n", B[i].coefficient, B[i].exponenet);
    }

    // 다항식 D 생성
    polynomial *D;
    // A+B 다항식 덧셈해줌, 출력
    D = padd(A, B);
    printf("3.2 다항식 덧셈\n다항식 덧셈 결과 : D(x)\n");
    printf("    coef    expon\n");
    draw(D, termCntArr[2]);

    // A*B 다항식 곱셈, 출력
    printf("3.3 다항식 곱셈\n");
    D = pmul(A, B);
    printf("D(x) 곱셈\n");
    draw(D, termCntArr[2]);

    // 동적할당 해제
    free(A);
    free(B);
    free(D);
}