#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void swap(char *a, char *b) {
    char temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void perm(char *list, int i, int n) {
    if (i == n) {
        printf("%s ", list);
    } else {
        for (int j = i; j < n; j++) {
            swap(list + i, list + j);
            perm(list, i + 1, n);
            swap((list + i), (list + j));
        }
    }
}

void draw(int *list, int n) {

    for (int i = 0; i < n; i++) {
        printf("%d", *(list + i));
    }
    printf("\t");
}

void swap(int *a, int *b) {
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void perm(int *list, int i, int n) {
    if (i == n) {
        draw(list, n);
    } else {
        for (int j = i; j < n; j++) {
            swap(list + i, list + j);
            perm(list, i + 1, n);
            swap((list + i), (list + j));
        }
    }
}

int main(void) {

    char A[4][10] = {"GO", "BOY",
"GIRL", "GIRLS"};
    for (int i = 0; i < 4; i++) {
        int len = strlen(A[i]);
        perm(A[i], 0, len);
        printf("\n");
    }


    printf("2.2. 1부터 n사이의 숫자들을 이용한 순열\n");
    while (1) {
        int tempLen = 0;
        printf("입력 : ");
        scanf("%d", &tempLen);
        if (tempLen == -1) {

            printf("종료 \n");
            break;
        }
        int *arr = (int *) malloc(sizeof(int) * tempLen);
        for (int i = 0; i < tempLen; i++) {
            arr[i] = i + 1;
        }
        printf("순열 : \n");
        perm(arr, 0, tempLen);
        printf("\n");
        free(arr);
    }

    printf("2.3. 순열 원소 개수를 변화시키면서 실행 시간 관찰\n");
    double time[10];
    for (int i = 1; i <= 10; i++) {
        int *arr = (int *)malloc(sizeof(int) * i);
        for (int j = 0; j < i; j++) {
            arr[j] = j+1;
        }
        clock_t start, end;
        start = clock();
        perm(arr, 0, i);
        end = clock();
        time[i] = (double)(end-start) / CLOCKS_PER_SEC;
        printf("\n");
        free(arr);
    }
    printf("  원소갯수    실행시간\n");
    for (int i = 0; i < 10; i++) {
        printf("%6d %14.3lf\n", i+1, time[i]);
    }

    return 0;
}