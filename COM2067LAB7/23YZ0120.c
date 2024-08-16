#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *left;
    struct node *right;
    int height;
};

struct node *createNode(int data){
    struct node *newNode=(struct node*)malloc(sizeof(struct node));
    newNode->data=data;
    newNode->left=newNode->right=NULL;
    newNode->height=1;
    return newNode;
}

int height(struct node *node){
    if(node==NULL) return 0;
    return node->height;
}

int max(int a, int b){
    return a>b ? a:b;
}

struct node *rightRotate(struct node *y){
    struct node *x=y->left, *t=x->right;
    x->right=y;
    y->left=t;

    y->height=max(height(y->left),height(y->right))+1;
    x->height=max(height(x->left),height(x->right))+1;

    return x;
}

struct node *leftRotate(struct node *x){
    struct node *y=x->right, *t=y->left;
    y->left=x;
    x->right=t;

    x->height=max(height(x->left),height(x->right))+1;
    y->height=max(height(y->left),height(y->right))+1;

    return y;
}


int getBalance(struct node *node){
    if(node==NULL) return 0;
    return height(node->left)-height(node->right);
}

struct node *insert(struct node *node, int data){
    int balance;
    if(node==NULL) return createNode(data);
    if(data<node->data) node->left = insert(node->left,data);
    else node->right = insert(node->right,data);

    node->height = max(height(node->left),height(node->right)) +1;

    balance=getBalance(node);

    if(balance>1 && data < node->left->data)
        return rightRotate(node);
    if(balance<-1 && data > node->right->data)
        return leftRotate(node);
    if(balance>1 && data>node->left->data){
        node->left=leftRotate(node->left);
        return rightRotate(node);
    }
    if(balance<-1 && data<node->right->data){
        node->right=rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}
void inorder(struct node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d\n", root->data);
        inorder(root->right);

    }
}

void printFormat(struct node *root, struct node *parent, int level, char *childType, int *isFirst) {
    if (root == NULL) return;

    if (level == 1) {
        if (!(*isFirst)) {
            printf(" ");
        }
        int balance = getBalance(root);
        if (parent == NULL) {
            printf("%d (-1 B)", root->data);
        } else {
            printf("%d (%d %s) (%d B)", root->data, parent->data, childType, balance);
        }
        *isFirst = 0;
    } else if (level > 1) {
        printFormat(root->left, root, level-1, "L", isFirst);
        printFormat(root->right, root, level-1, "R", isFirst);
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
        printFormat(root, NULL, i, "", &isFirst);
        printf("\n");
    }
    printf("\n"); 
}

int main(){
    struct node *tree=NULL;
    int value;
    while(1){
        scanf("%d",&value);
        if(value==-1) break;
        tree=insert(tree,value);
    }
    inorder(tree);
    printf("\n");
    printTree(tree);

    return 0;
}
