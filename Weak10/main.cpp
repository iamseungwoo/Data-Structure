#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    node *link;
} node;

// 노드 개수
int n;

// dfs 함수
void dfs(int visited[], node *graph_node, int idx) {
    // 이미 방문한 노드라면 return
    if (visited[idx]) {
        return;
    }
    // 방문 체크
    visited[idx] = 1;
    // 노드 자신 출력
    printf("    %d", idx);
    // null 이 될 때까지 반복
    for (node *i = graph_node[idx].link; i != nullptr; i = i->link) {
        // dfs recursion
        dfs(visited, graph_node, i->data);
    }
}

// dfs 신장 트리, dfs와 동일하게 구성
void dfs_tree(int visited[], node *graph_node, int idx) {

    visited[idx] = 1;
    for (node *i = graph_node[idx].link; i != nullptr; i = i->link) {
        if (visited[i->data]) {
            continue;
        }
        printf("  (%d,", idx);
        printf(" %d)", i->data);
        dfs_tree(visited, graph_node, i->data);
    }
}

// bfs
void bfs(int visited[], node *graph_node, int idx) {
    // 배열 기반 큐 생성
    int *q = new int[n];
    q[0] = idx;
    // 방문처리
    visited[idx] = 1;
    // front, rear 설정
    int front;
    int rear = 0;

    printf("    %d", q[rear++]);
    node *temp;
    for (front = 0, q[rear++] = idx; front < rear; front++) {
        for (temp = graph_node[q[front]].link; temp != nullptr; temp = temp->link) {
            if (visited[temp->data]) {
                continue;
            }
            printf("    %d", temp->data);
            visited[temp->data] = 1;
            q[rear++] = temp->data;
        }
    }
}

// bfs 신장트리, bfs 와 동일함.
void bfs_tree(int visited[], node *graph_node, int idx) {
    int *q = new int[n];
    q[0] = idx;
    visited[idx] = 1;
    node *temp;
    int front;
    int rear = 1;
    for (front = 0, q[rear++] = idx; front < rear; front++) {
        for (temp = graph_node[q[front]].link; temp != nullptr; temp = temp->link) {
            if (visited[temp->data]) {
                continue;
            }
            printf("  (%d, ", q[front]);
            printf("%d)", temp->data);
            visited[temp->data] = 1;
            q[rear++] = temp->data;
        }
    }
}

int main() {
    while (1) {
        printf("10.1. 인접 리스트 형태의 무방향성 그래프 생성\n");
        printf("  노드 개수(n): ");
        scanf("%d", &n);

        if (n == -1) {
            break;
        }

        node *graph = (node *) calloc(n, sizeof(node));

        int max_degree_idx = 0;
        // non-direct graph
        while (1) {
            int a, b;
            printf("  에지 정보(vi vj) : ");
            scanf("%d %d", &a, &b);

            if (a == -1) {
                break;
            }

            node *temp1 = (node *) malloc(sizeof(node));
            temp1->data = b;
            temp1->link = nullptr;
            if (graph[a].link != nullptr) {
                temp1->link = graph[a].link;
            }
            graph[a].link = temp1;
            // a노드의 degree를 graph[a].data 넣음
            graph[a].data += 1;

            node *temp2 = (node *) malloc(sizeof(node));
            temp2->data = a;
            temp2->link = nullptr;
            if (graph[b].link != nullptr) {
                temp2->link = graph[b].link;
            }
            graph[b].link = temp2;
            // b노드의 degree를 graph[a].data에 넣음
            graph[b].data += 1;

            // max degree를 가진 idx 판별
            max_degree_idx = graph[(graph[a].data > graph[b].data ? a : b)].data > graph[max_degree_idx].data
                             ? (graph[a].data > graph[b].data ? a : b) : max_degree_idx;

        }

        // print graph
        for (int i = 0; i < n; ++i) {
            printf("   [%d]:  ", i);
            for (node *j = graph[i].link; j != nullptr; j = j->link) {
                printf("%d -> ", j->data);
            }
            printf("end\n");
        }

        printf("\n  degree가 가장 큰 노드와 degree 값 : 노드 %d, degree %d\n", max_degree_idx, max_degree_idx);
        printf("   [%d]:  ", max_degree_idx);
        for (node *j = graph[max_degree_idx].link; j != nullptr; j = j->link) {
            printf("%d -> ", j->data);
        }
        printf("end\n");

        printf("10.2. 탐색 알고리즘(DFS, BFS)\n");
        printf("  깊이 우선 탐색 (DFS)\n");
        for (int i = 0; i < 5; i += 2) {
            printf("  시작노드 %d :", i);
            int *visited = (int *) calloc(n + 1, sizeof(int));
            dfs(visited, graph, i);
            free(visited);
            printf("\n");
        }

        printf("  넓이 우선 탐색 (BFS)\n");
        for (int i = 1; i <= n; i += 2) {
            printf("  시작노드 %d :", i);
            int *visited = (int *) calloc(n + 1, sizeof(int));
            bfs(visited, graph, i);
            free(visited);
            printf("\n");
        }

        printf("10.3. 신장트리 알고리즘(DFS, BFS 기반)\n");
        printf("  DFS 신장트리\n");
        for (int i = 0; i < n; i += 2) {
            printf("  시작노드 %d :", i);
            int *visited = (int *) calloc(n + 1, sizeof(int));
            dfs_tree(visited, graph, i);
            free(visited);
            printf("\n");
        }
        printf("  BFS 신장트리\n");
        for (int i = 1; i <= n; i += 2) {
            printf("  시작노드 %d :", i);
            int *visited = (int *) calloc(n + 1, sizeof(int));
            bfs_tree(visited, graph, i);
            free(visited);
            printf("\n");
        }
    }
    return 0;
}
