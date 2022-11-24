#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node {
    int data;
    node *lchild;
    node *rchild;
} node;

void printData(int data) {
    printf(" %d", data);
}

/** 중위 순회 */
void InorderTraverse(node *bTreeNode) {
    if (bTreeNode == NULL) return;
    InorderTraverse(bTreeNode->lchild);
    printData(bTreeNode->data);
    InorderTraverse(bTreeNode->rchild);
}

void PreorderTraverse(node *bTreeNode) {
    if (bTreeNode == NULL) return;
    printData(bTreeNode->data);
    PreorderTraverse(bTreeNode->lchild);
    PreorderTraverse(bTreeNode->rchild);
}

void PostorderTraverse(node *bTreeNode) {
    if (bTreeNode == NULL) return;
    PostorderTraverse(bTreeNode->lchild);
    PostorderTraverse(bTreeNode->rchild);
    printData(bTreeNode->data);
}


node *make_node() {
    node *n = (node *) malloc(sizeof(node));
    n->rchild = NULL;
    n->lchild = NULL;

    return n;
}

node *make_tree_by_code() {
    node *root = make_node();
    root->data = 5;

    node *c1 = make_node();
    c1->data = 3;

    node *c2 = make_node();
    c2->data = 8;

    node *c3 = make_node();
    c3->data = 1;

    node *c4 = make_node();
    c4->data = 4;

    root->lchild = c1;
    root->rchild = c2;
    c1->lchild = c3;
    c1->rchild = c4;

    return root;
}

node *copy(node *original) { // original 트리를 복사한 새로운 이진 트리를 반환
    struct node *temp;
    if (original) {
        temp = (struct node *) malloc(sizeof(struct node));
        temp->lchild = copy(original->lchild);
        temp->rchild = copy(original->rchild);
        temp->data = original->data;
        return temp;
    }
    return NULL;
}

int equal(node *first, node *second) {
/* first와 second 트리가 다를 경우 FALSE를 반환. 트리가 동일할 경우, TRUE를 반환 */
    return ((!first && !second) || (first && second && (first->data == second->data) &&
                                    equal(first->lchild, second->lchild) && equal(first->rchild, second->rchild)));
}

node *swap(node *original) {
    node *temp;
    if (original) {
        temp = (struct node *) malloc(sizeof(struct node));
        temp->rchild = swap(original->lchild);
        temp->lchild = swap(original->rchild);
        temp->data = original->data;
        return temp;
    }
    return NULL;
}

node *make_random_tree(int d, int n) {
    node *root = make_node();
    node *nd = root;
    nd->data = d;

    srand(time(NULL));
    while (d < n) {
        if (rand() % 2 == 0) {
            if (nd->lchild != NULL) {
                nd = nd->lchild;
                continue;
            }
            nd->lchild = make_node();
            nd->lchild->data = ++d;
        } else {
            if (nd->rchild != NULL) {
                nd = nd->rchild;
                continue;
            }
            nd->rchild = make_node();
            nd->rchild->data = ++d;
        }
        nd = root;
    }
    return root;
}

int main() {
    node *A = make_tree_by_code();

    printf("8.1.2. 트리 순회 (A)\n");
    printf("inorder(A) :");
    InorderTraverse(A);
    printf("\n");

    printf("preorder(A) :");
    PreorderTraverse(A);
    printf("\n");

    printf("postorder(A) :");
    PostorderTraverse(A);
    printf("\n");

    // -------------------------------------
    printf("\n8.2.1. 트리 복사 (B = copy(A))\n");
    node *B = copy(A);
    printf("8.1.2. 트리 순회 (B)\n");
    printf("inorder(B) :");
    InorderTraverse(B);
    printf("\n");

    printf("preorder(B) :");
    PreorderTraverse(B);
    printf("\n");

    printf("postorder(B) :");
    PostorderTraverse(B);
    printf("\n");

    // -----------------------------------
    printf("\n8.2.3. 트리 동질성 검사 (equal(A,B))\n");
    printf("equal(A, B) : ");
    if (equal(A, B)) {
        printf("TRUE");
    } else {
        printf("FALSE");
    }

    // --------------------------------
    printf("8.2.4. 트리 swap (C = swap(A))\n"
           "8.2.5. 트리 순회 (C)\n");
    node *C = swap(A);
    printf("inorder(C) :");
    InorderTraverse(C);
    printf("\n");

    printf("preorder(C) :");
    PreorderTraverse(C);
    printf("\n");

    printf("postorder(C) :");
    PostorderTraverse(C);
    printf("\n");

    // ------------------------------
    printf("8.3.1. 랜덤 트리 자동 생성 (D)\n");
    printf("Input n : ");
    int n;
    scanf("%d", &n);
    node *D = make_random_tree(1, n);

    printf("inorder(C) :");
    InorderTraverse(D);
    printf("\n");

    printf("preorder(C) :");
    PreorderTraverse(D);
    printf("\n");

    printf("postorder(C) :");
    PostorderTraverse(D);
    printf("\n");
}