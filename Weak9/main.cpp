#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

typedef struct node {
    int key;
    double value;
    node *lchild;
    node *rchild;
} node;

node *modified_search(node *tree, int key) {
    for (node *ptr = tree; ptr != nullptr;) {
        if (ptr->key == key) {
            return nullptr;
        }
        if (key < ptr->key) {
            if (ptr->lchild == nullptr) {
                return ptr;
            } else {
                ptr = ptr->lchild;
            }
        } else { // key > ptr->key
            if (ptr->rchild == nullptr) {
                return ptr;
            } else {
                ptr = ptr->rchild;
            }
        }
    }
    // tree가 null일 때
    return nullptr;
};


void insert_node(struct node **root, int key) {
// node: root, num: 추가할 키 값.
    node *ptr, *parent = modified_search(*root, key);
    if (parent || !(*root)) { // num이 tree에 존재하지 않음.
        ptr = (struct node *) malloc(sizeof(struct node));
        ptr->key = key; // num을 키 값으로 하는 노드 생성
        ptr->value = 1.0 / key;
        ptr->lchild = ptr->rchild = nullptr;
        if (*root) { // parent의 child node로 삽입
            if (key < parent->key) {
                parent->lchild = ptr;
            } else {
                parent->rchild = ptr;
            }
        } else {
            *root = ptr; // 트리가 empty일 경우, root로 등록
        }
    }
}

// count 변수
int cnt;

node *iterSearch(node *tree, int key) {


// key를 포함하고 있는 노드의 포인터를 return // 해당되는 노드가 없을 경우, return nullptr.
// Iterative version
    while (tree != nullptr) {
        if (key == (tree)->key) return tree;
        if (key < (tree)->key) {
            tree = (tree)->lchild;
        } else {
            tree = (tree)->rchild;
        }
        ++cnt;
    }
    return nullptr;
}

// node 개수 counting 함수
int count_node(node *ptr) {
    int count = 0;
    if (ptr != nullptr) {
        count = 1 + count_node(ptr->lchild) + count_node(ptr->rchild);
    }
    return count;
}

// 깊이 탐색
int count_depth(node *ptr) {
    // null pointer 경우 0 반환
    if (ptr == nullptr) {
        return 0;
    }
    int left = count_depth(ptr->lchild);

    int right = count_depth(ptr->rchild);

    // 왼쪽이 비었을 때
    if (ptr->lchild == nullptr) {
        return 1 + right;
    }
    // 오른쪽이 비었을 때
    if (ptr->rchild == nullptr) {
        return 1 + left;
    }

    return max(left, right) + 1;
}

// 단말 노드 개수
int count_leaf(node *ptr) {
    if (ptr == nullptr) {
        return 0;
    } else if (ptr->lchild == nullptr && ptr->lchild == nullptr) {
        return 1;
    } else {
        return count_leaf(ptr->lchild) + count_leaf(ptr->rchild);
    }
};

// inorder 순회
void inorder_traversal(node *tree) {

    if (tree == nullptr) {
        return;
    }

    inorder_traversal(tree->lchild);
    cout << "key: " << tree->key << ", value: " << tree->value << "\n";
    inorder_traversal(tree->rchild);
}

// node 만드는 함수
node *make_node() {
    auto tree = (node *) malloc(sizeof(node));
    tree->rchild = nullptr;
    tree->lchild = nullptr;

    return tree;
}

// binary search tree 만들기 n 값에 따라 노드 추가횟수 달라짐
node *make_bst(int n) {
    node *root = make_node();
    node *ptr = root;
    int key = (double) rand() / (double) (0x7fff);
    double value = 1.0 / key;

    ptr->key = key;
    ptr->value = value;

    --n;
    for (; n > 0; --n) {
        key = (double) rand() / (double) (0x7fff);
        insert_node(&root, key);
    }
    return root;
}

void remove_node(node **tree, int key) {
    // 부모 노드
    node *parent_node;
    // 현재 노드
    node *current_node = *tree;
    // 삭제 될 노드
    node *delete_node;
    // 현재 노드가 key를 만나거나 null이 될때 까지 이동 parent 포인터 계속 업데이트
    while (current_node != nullptr && current_node->key != key) {
        parent_node = current_node;
        if (current_node->key < key) {
            current_node = current_node->rchild;
        } else {
            current_node = current_node->lchild;
        }
    }

    delete_node = current_node;

    if (current_node == nullptr) {
        cout << "해당 노드를 찾을 수 없습니다.";
        return;
    }

    if (delete_node->lchild == nullptr && delete_node->rchild == nullptr) { // 단말 노드 일 때
        // 삭제될 노드가 부모노드의 lchild인지 rchild인지 찾는 것
        if (parent_node->key > delete_node->key) {
            parent_node->lchild = nullptr;
        } else {
            parent_node->rchild = nullptr;
        }
    } else if (delete_node->lchild == nullptr) {    // right child만 있을 때
        if (parent_node->key > delete_node->key) {
            parent_node->lchild = delete_node->rchild;
        } else {
            parent_node->rchild = delete_node->rchild;
        }
    } else if (delete_node->rchild == nullptr) {    // left child만 있을 때
        if (parent_node->key > delete_node->key) {
            parent_node->lchild = delete_node->lchild;
        } else {
            parent_node->rchild = delete_node->lchild;
        }
    } else {
        // 삭제될 노드의 오른쪽 노드에서 제일 왼쪽 노드 찾아서
        node *delete_left_sub = delete_node->rchild;
        while (delete_left_sub->lchild != nullptr) {
            delete_left_sub = delete_left_sub->lchild;
        }

        // 삭제될 노드의 왼쪽 노드를 넣어줌.
        delete_left_sub->lchild = delete_node->lchild;


        if (parent_node->key > delete_node->key) {
            parent_node->lchild = delete_node->rchild;
        } else {
            parent_node->rchild = delete_node->rchild;
        }
    }

    cout << "key: " << delete_node->key << ", value: " << delete_node->value << "가 삭제 되었습니다.\n";
    free(delete_node);
}

int key_set[12] = {10, 6, 15, 8, 18, 12, 3, 14, 9, 20, 5, 2};

int main() {
    cout << "9.1. 12개의 (key, value)쌍을 생성하여 이진 탐색 트리 생성\n";
    node *A = make_node();
    A->key = key_set[0];
    A->value = 1.0 / key_set[0];
    for (int i = 1; i < 12; i++) {
        insert_node(&A, key_set[i]);
    }
    inorder_traversal(A);
    cout << "생성 완료\n";

    // binary search tree delete implement
    cout << "추가 기능 이진 검색 트리 삭제 기능\n";
    int delete_key;
    while(true) {
        cout << "삭제하고 싶은 key를 입력하세요. -1 입력시 종료";
        cin >> delete_key;
        if (delete_key == -1) {
            break;
        }
        remove_node(&A, delete_key);
    }

    cout << "9.2. 생성된 이진 검색 트리에서 key값을 활용한 검색\n";
    int k;
    while (true) {
        cout << "찾고자 하는 key 값을 입력하세요. : ";
        cin >> k;
        if (k == -1) {
            break;
        }
        cnt = 1;
        node *temp = iterSearch(A, k);
        if (temp == nullptr) {
            cout << k << "는 없습니다.\n";
            continue;
        }
        cout << "count : " << cnt << " , key: " << k << "의 value: " << temp->value << "\n";
    }

    cout << "9.3. n개의 노드를 가진 이진트리 생성시간 및 노드 수, 높이(깊이), 단말 노드 수 관찰\n";
    int n;
    clock_t start_time, end_time;
    float time;
    while (true) {
        cout << "n개의 노드를 가진 이진검색 트리 생성 (n) : ";
        cin >> n;
        if (n == -1) {
            break;
        }
        cout << "이진검색트리 B :\n";
        start_time = clock();
        node *B = make_bst(n);
        end_time = clock();
        time = (float) (end_time - start_time) / CLOCKS_PER_SEC;
        inorder_traversal(B);
        cout << "이진검색트리 B의 생성시간: " << time << endl;
        cout << "이진검색트리 B의 노드 수 : " << count_node(B) << endl;
        cout << "이진검색트리 B의 높이(깊이) :" << count_depth(B) << endl;
        cout << "이진검색트리 B의 단말노드 수 : " << count_leaf(B) << endl;
    }
    return 0;
}
