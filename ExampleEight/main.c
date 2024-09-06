#include <stdio.h>
#include <stdlib.h>

#define RED 0
#define BLACK 1
struct node {
    int data;
    struct node *left, *right, *parent;
    int color;
};

struct node *createNode(int data) {
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->left = newNode->right = newNode->parent = NULL;
    newNode->color = RED;
    return newNode;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

struct node *leftRotate(struct node *root, struct node *x) {
    struct node *y;
    y= x->right;
    x->right = y->left;

    if (y->left != NULL)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;

    return root;
}

struct node *rightRotate(struct node *root, struct node *y) {
    struct node *x;
    x= y->left;
    y->left = x->right;
    if (x->right != NULL)
        x->right->parent = y;

    x->parent = y->parent;

    if (y->parent == NULL)
        root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;

    return root;
}

struct node *insertFixup(struct node *root, struct node *z) {
    while (z->parent != NULL && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            struct node *y = z->parent->parent->right;
            if (y != NULL && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    root = leftRotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                root = rightRotate(root, z->parent->parent);
            }
        } else {
            struct node *y = z->parent->parent->left;
            if (y != NULL && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    root = rightRotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                root = leftRotate(root, z->parent->parent);
            }
        }
    }
    root->color = BLACK;
    return root;
}

struct node *insert(struct node *root, int data) {
    struct node *z = createNode(data);
    struct node *y = NULL;
    struct node *x = root;

    while (x != NULL) {
        y = x;
        if (z->data < x->data)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (y == NULL)
        root = z;
    else if (z->data < y->data)
        y->left = z;
    else
        y->right = z;

    root = insertFixup(root, z);
    return root;
}

void inorder(struct node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d\n", root->data);
        inorder(root->right);
    }
}

void printLevel(struct node *root, struct node *parent, int level, char *relation, int *isFirst) {
    if (root == NULL) return;

    if (level == 1) {
        if (!(*isFirst)) printf(" ");
        printf("%d %s", root->data, root->color == RED ? "R" : "B");
        if (parent != NULL) {
            printf(" (%d %s)", parent->data, relation);
        }
        *isFirst = 0;
    } else if (level > 1) {
        printLevel(root->left, root, level - 1, "L", isFirst);
        printLevel(root->right, root, level - 1, "R", isFirst);
    }
}

int treeHeight(struct node *node) {
    if (node == NULL) return 0;
    int leftHeight = treeHeight(node->left);
    int rightHeight = treeHeight(node->right);
    return max(leftHeight, rightHeight) + 1;
}

void printTree(struct node *root) {
    int h = treeHeight(root);
    for (int i = 1; i <= h; i++) {
        int isFirst = 1;
        printLevel(root, NULL, i, "-", &isFirst);
        printf("\n");
    }
}

int main() {
    struct node *tree = NULL;
    int value;

    while (1) {
        scanf("%d", &value);
        if (value == -1) break;
        tree = insert(tree, value);
    }

    inorder(tree);
    printf("\n");
    printTree(tree);

    return 0;
}
