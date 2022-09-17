#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/** 1.2 에서 쓰이는 정렬 array. main 함수에서 1000000크기 쓰면 stack이 터지기 때문에 전역에서 설정 해주어야함.*/
int A2[1000000];

/** swap 함수 a, b를 포인터로 받아서 값을 swap 해줌 */
void swap(int *a, int *b) {
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

/** select sort*/
void sort(int list[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (list[min] > list[j]) min = j;
        }
        swap(&list[min], &list[i]);
    }
}

/** showing array. array와 array 길이를 인자로 매개 변수 list, len에 받는다. 20개 한번씩 줄바꿈해줌*/
void draw(int list[], int len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", list[i]);
        if ((i % 20) == 19) printf("\n");
    }
}

/** Verifying Array is sorted. array가 sorted 된지 검증하는 함수. 정렬되면 1반환 아니면 0반환*/
int is_sorted(int A[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (A[i] > A[i + 1]) return 0;
    }
    return 1;
}

/** 1.2에서 쓰이는 array A2를 초기화 시켜줌. 크기가 매번 바뀌어 다시 역순 정렬 해야해서. */
void initArray(int n) {
    for (int i = 0; i < n; i++) {
        A2[i] = 1000000 - i;
    }
}

/** 이진 탐색 using loop. while문을 사용한 이진탐색 searchnum이 mid 보다 크면 left = mid+1, 작으면 right = mid - 1. 찾을수 없으면 -1반환*/
int binsearch(int list[], int searchnum, int left, int right) {
    int counter = 0;
    while (left <= right) {
        counter++;
        int mid = (left + right) / 2;
        if (list[mid] > searchnum) {
            right = mid - 1;
        }
        if (list[mid] < searchnum) {
            left = mid + 1;
        }
        if (list[mid] == searchnum) {
            printf("list[mid]: %d\n", list[mid]);
            return counter;
        }
    }
    return -1;
}

int main() {
    int A[100000];
    for (int i = 0; i < 100000; i++) {
        A[i] = rand() % 100001;
    }
    printf("1.1. 무작위 100,000개 정수 생성 및 정렬, 정렬 검사 수행\n");
    printf("1.1.1. 배열 A에 100,000개의 정수를 무작위로 생성하여 저장\n");
    draw(A, 100000);

    printf("1.1.2. 배열 A에 무작위로 저장된 정수를 정렬\n");
    sort(A, 100000);
    draw(A, 100000);

    printf("1.1.3. 배열 A에 정렬된 정수의 정렬 상태 확인\n");
    (is_sorted(A, 100000)) ? printf("정렬 완료!\n") : printf("Not sorted\n");

    printf("1.2. 배열의 크기를 100부터 1,000,000까지 바꾸면서 sort 함수의 실행 시간 측정\n");
    printf("       n        시간   정렬상태");
    int updateSize = 100;
    for(int i = 100; i < 1000000; i+=updateSize) {
        if (i == 1000)  updateSize = 1000;
        if (i == 10000) updateSize = 10000;
        if (i == 100000)    updateSize = 100000;
        initArray(i);   // 배열 초기화
        clock_t start, stop;    // 시간 측정 변수 선언
        start = clock();    // 시간 측정 시작
        sort(A2, i);    // 정렬 시작
        stop = clock();     // 시간 측정 끝
        printf("%8d %12.3f 정렬됨\n", i, ((double) (stop - start))/CLOCKS_PER_SEC);
    }

    printf("1.3. 100,000개의 정수를 무작위로 생성하여 정렬 후 이진검색 수행\n");
    printf("1.3.1. 배열에 100,000개의 정수를 무작위로 생성하여 저장\n");
    for (int i = 0; i < 100000; i++) {
        A[i] = rand() % 100001;
    }
    printf("완료.\n");
    printf("1.3.2. 배열에 무작위로 저장된 정수 정렬\n");
    sort(A, 100000);
    printf("완료.\n");
    printf("1.3.3. 배열에 정렬된 정수의 정렬 상태 확인\n");
    // is_sorted가 1을 반환하면 정렬완료, 아니면 정렬안됨 출력
    is_sorted(A, 100000) ? printf("정렬 완료!!!\n") : printf("정렬 안됨\n");
    int input = 0;
    while (input != -1) {
        printf("검색 데이터( 1 ~ 100000 ) : ");
        scanf("%d", &input);
        // 검색 범위 벗어나면 검색 종료
        if (input < 1 || input > 100000) {
            printf("검색 종료.\n");
            break;
        }
        printf("검색 데이터 : %9d\tCounter %d: \n", input, binsearch(A, input, 0, 99999));
    }

    printf("1.4.1. 배열에 50000개의 정수를 역순으로 생성하여 저장\n");
    int A3[50000];
    // A3 역순 정렬 생성
    for (int i = 0; i < 50000; i++) {
        A3[i] = 50000 - i;
    }
    printf("1.4.2. 배열에 저장된 50000개의 정수 정렬\n");
    sort(A3, 50000);
    printf("1.4.3. 배열에 정렬된 정수의 정렬 상태 확인");
    (is_sorted(A, 50000)) ? printf("정렬 완료!\n") : printf("Not sorted\n");

    input = 0;
    while (input != -1) {
        printf("검색 데이터( 1 ~ 50000 ) : ");
        scanf("%d", &input);
        if (input < 1 || input > 50000) {
            printf("검색 종료.\n");
            break;
        }
        printf("검색 데이터 : %9d\tCounter %d: \n", input, binsearch(A3, input, 0, 49999));
    }
    return 0;
}
