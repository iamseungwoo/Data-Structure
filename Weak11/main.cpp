#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// 방향성 그래프 edge 가중치, 인접 Matrix
int **cost;
// vertex 개수
int n;

// 데이터 입력
void input() {
    printf("  노드 수 (n) : ");
    scanf("%d", &n);
    // n == -1일 때 프로그램 종료
    if (n == -1) {
        exit(0);
    }
    cost = (int **) malloc(sizeof(int *) * n);

    // 동적할당 & 99999로 초기화(연결안된 상태 inf)
    for (int i = 0; i < n; i++) {
        cost[i] = (int *) malloc(sizeof(int) * n);
        for (int j = 0; j < n; j++) {
            cost[i][j] = 99999;
        }
        cost[i][i] = 0;
    }

    // 데이터 입력
    int from, to, w;
    while (1) {
        printf("  에지 정보 (from to weight) : ");
        scanf("%d %d %d", &from, &to, &w);
        if (from < 0 || to < 0 || w < 0) break;
        cost[from][to] = w;
    }

    // 입력된 그래프 출력
    printf("  인접 행렬을 이용한 그래프의 구성 :\n");
    printf("         [ 0]   [ 1]   [ 2]   [ 3]   [ 4]   [ 5]\n");
    for (int i = 0; i < n; i++) {
        printf("  [ %d]", i);
        for (int j = 0; j < n; j++) {
            printf("%8d", cost[i][j]);
        }
        printf("\n");
    }
}

// vertex 에서 가장 가중치가 작고 방문하지 않은 노드 선택
int choose(int distance[], int numOfV, short int found[]) {
    int i, Min = INT_MAX, minPos = -1;

    for (i = 0; i < numOfV; i++) {
        if (found[i] || Min <= distance[i]) continue;

        Min = distance[i];
        minPos = i;
    }
    return minPos;
}

// dijkstra algorithm 구현
void shortestpath(int v, int distance[], short int found[]) {
    int i, u, w;
    for (i = 0; i < n; i++) {
        distance[i] = cost[v][i];
        found[i] = 0;
    }
    found[v] = 1;
    distance[v] = 0;

    for (i = 0; i < n - 2; i++) {
        u = choose(distance, n, found);
        found[u] = 1;
        for (w = 0; w < n; w++) {
            if (found[w] || cost[u][w] + distance[u] > distance[w]) continue;
            distance[w] = cost[u][w] + distance[u];
        }
    }

    printf("  Distance :");
    for (i = 0; i < n; i++) {
        printf("%6d", distance[i]);
    }
    printf("\n");
}

// dijkstra algorithm 의 각 경로마다 실행되게 하게끔 while문으로 묶은것
void dijkstraImpl() {
    while (1) {
        short int *found = (short int *) malloc(sizeof(short int) * n);
        int *distance = (int *) malloc(sizeof(int) * n);

        int v;
        printf("  시작 노드 (v) : ");
        scanf("%d", &v);
        if (v == -1) break;
        shortestpath(v, distance, found);
    }
}

// allcosts 알고리즘
void allcosts() {
    int i, j, k;
    int **distance = (int **) malloc(sizeof(int *) * n);

    for (i = 0; i < n; i++) {
        distance[i] = (int *) malloc(sizeof(int) * n);
        for (j = 0; j < n; j++) {
            distance[i][j] = cost[i][j];
        }
    }

    for (k = 0; k < n; k++)
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                if (distance[i][k] + distance[k][j] < distance[i][j])
                    distance[i][j] = distance[i][k] + distance[k][j];
    // allcosts 출력
    printf("\n          [ 0]   [ 1]   [ 2]   [ 3]   [ 4]   [ 5]\n");
    for (i = 0; i < n; i++) {
        printf("   [ 0]");
        for (j = 0; j < n; j++) {
            printf("%7d", distance[i][j]);
        }
        printf("\n");
    }
}

int main() {
    while (1) {
        printf("11.1. 인접 행렬 형태의 방향성 그래프 생성\n");
        input();

        printf("11.2. 최단 경로 (단일 출발점)\n");
        dijkstraImpl();

        printf("\n11.3. 최단 경로 (모든 경로)\n  All Path Distance :");
        allcosts();
    }
    return 0;
}
