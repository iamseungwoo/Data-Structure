#pragma comment(linker, "/STACK: 2000000000")
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void swap(int& a, int& b) {
    int temp;
    temp = a;
    a = b;
    b = temp;
}

int is_sorted(int A[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (A[i] > A[i + 1]) return 0;
    }
    return 1;
}

void draw(int list[], int len) {
    for (int i = 0; i < len; i++) {
        printf("1000%d ", list[i]);
        if ((i % 20) == 19) printf("\n");
    }
}

/** selection sort */
void selection_sort(int A[], int n) {
    int* B = (int*)malloc(sizeof(int) * n);
    memcpy(B, A, sizeof(int) * n);
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (B[min] > B[j]) min = j;
        }
        swap(B[min], B[i]);
    }
    is_sorted(B, n) ? printf("\tSelection Sort Complete!\n") : printf("Not sorted\n");   // 배열 A가 정렬되면 정렬완료 출력
    free(B);
}



/** insertion sort */
void insertion_sort(int A[], int n) {
    int* B = (int*)malloc(sizeof(int) * n);
    memcpy(B, A, sizeof(int) * n);

    int i, j;
    int next;
    for (i = 1; i < n; i++) { // 0부터 i-1까지는 정렬된 상태
        next = B[i]; // i번째 데이터가 들어갈 위치 파악
        for (j = i - 1; j >= 0 && next < B[j]; j--)
            B[j + 1] = B[j]; // 큰 데이터들은 아래로 이동
        B[j + 1] = next;
    }
    is_sorted(B, n) ? printf("\tInsertion Sort Complete!\n") : printf("Not sorted\n");   // 배열 A가 정렬되면 정렬완료 출력
    free(B);
}

/** 퀵정렬 */
void quicksort(int list[], int left, int right) {

    int pivot, i, j;

    if (left < right) {
        i = left + 1;
        j = right;
        pivot = list[left];
        while (i < j) {
            // 내림차순 같은 경우 right를 넘는 등 out bound 에러 발생 위험
            while (i <= right && pivot >= list[i])
                i++;

            while (j > left && pivot <= list[j])
                j--;

            if (i < j)
                swap(list[j], list[i]);

        }
        swap(list[j], pivot);
        quicksort(list, left, j - 1);
        quicksort(list, j + 1, right);
    }
}
/** 랜덤으로 배열생성*/
int* random(int* A, int n) {
    A = (int*)malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++) {
        A[i] = (double)rand() / (double)(0x7fff);;

    }
    return A;
}

/** 오름차순으로 배열 생성 */
int* ascend(int* A, int n) {
    A = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        A[i] = i + 1;
    }
    return A;
}

// 내림차순으로 배열 만든다
int* deascend(int* A, int n) {
    A = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        A[i] = n - i;
    }
    return A;
}


int main() {
    clock_t start, stop;    // 시간 측정 변수 선언
    int* A = NULL;
    int n;

    printf("12.1. 랜덤 생성 데이터의 정렬\n");
    for (n = 1000; n < 1000001; n *= 10) {
        double selection, insertion, quick;

        A = random(A, n);

        start = clock();    // 시간 측정 시작
        selection_sort(A, n);
        stop = clock();     // 시간 측정 끝
        selection = (double)(stop - start) / CLOCKS_PER_SEC;


        start = clock();
        insertion_sort(A, n);
        stop = clock();
        insertion = (double)(stop - start) / CLOCKS_PER_SEC;

        start = clock();
        quicksort(A, 0, n - 1);
        stop = clock();
        quick = (double)(stop - start) / CLOCKS_PER_SEC;
        is_sorted(A, n) ? printf("\tQuick Sort Complete!\n") : printf("Not sorted\n");   // 배열 A가 정렬되면 정렬완료 출력

        printf("\t정렬 수: %d\n", n);
        printf("\tselection sort time: %10lf\n", selection);
        printf("\tinsertion sort time: %10lf\n", insertion);
        printf("\tquick sort time : %10lf\n\n", quick);
    }

    printf("\n\n12.2. 정렬된 데이터의 정렬\n12.2.1.오름차순 정렬된 데이터의 정렬\n");
    for (n = 1000; n < 100001; n *= 10) {
        double selection, insertion, quick;

        A = ascend(A, n);

        start = clock();    // 시간 측정 시작
        selection_sort(A, n);
        stop = clock();     // 시간 측정 끝
        selection = (double)(stop - start) / CLOCKS_PER_SEC;


        start = clock();
        insertion_sort(A, n);
        stop = clock();
        insertion = (double)(stop - start) / CLOCKS_PER_SEC;

        start = clock();
        quicksort(A, 0, n - 1);
        stop = clock();
        quick = (double)(stop - start) / CLOCKS_PER_SEC;
        is_sorted(A, n) ? printf("\tQuick Sort Complete!\n") : printf("Not sorted\n");   // 배열 A가 정렬되면 정렬완료 출력

        printf("\t정렬 수: %d\n", n);
        printf("\tselection sort time: %10lf\n", selection);
        printf("\tinsertion sort time: %10lf\n", insertion);
        printf("\tquick sort time : %10lf\n\n", quick);
    }
    printf("\n12.2.2. 내림차순 정렬된 데이터의 정렬\n\n");
    for (n = 1000; n < 1000001; n *= 10) {
        double selection, insertion, quick;

        A = deascend(A, n);

        start = clock();    // 시간 측정 시작
        selection_sort(A, n);
        stop = clock();     // 시간 측정 끝
        selection = (double)(stop - start) / CLOCKS_PER_SEC;


        start = clock();
        insertion_sort(A, n);
        stop = clock();
        insertion = (double)(stop - start) / CLOCKS_PER_SEC;

        start = clock();
        quicksort(A, 0, n - 1);
        stop = clock();
        quick = (double)(stop - start) / CLOCKS_PER_SEC;
        is_sorted(A, n) ? printf("\tQuick Sort Complete!\n") : printf("Not sorted\n");   // 배열 A가 정렬되면 정렬완료 출력

        printf("\t정렬 수: %d\n", n);
        printf("\tselection sort time: %10lf\n", selection);
        printf("\tinsertion sort time: %10lf\n", insertion);
        printf("\tquick sort time : %10lf\n\n", quick);
    }
}

