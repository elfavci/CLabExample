#include <stdio.h>
#include <stdlib.h>

struct node{
    int id;
    int grade;
    struct node *left;
    struct node *right;
};

struct node *createNode(int id, int grade){
    struct node *newNode;
    newNode=(struct node*)malloc(sizeof(struct node));
    newNode->id=id;
    newNode->grade=grade;
    newNode->left=NULL;
    newNode->right=NULL;
    return newNode;
}

struct node *insert(struct node *treeNode, int id,int grade){
    if(treeNode==NULL){
        return createNode(id,grade);
    }
    if(grade<treeNode->grade){
        treeNode->left=insert(treeNode->left,id,grade);
    }
    else{
        treeNode->right=insert(treeNode->right,id,grade);
    }
    return treeNode;
}

int treeHeight(struct node *treeNode){
    if(treeNode==NULL){
        return  0;
    }
    int leftH=treeHeight(treeNode->left);
    int rightH=treeHeight(treeNode->right);
    return (leftH>rightH)?(leftH+1):(rightH+1);
}

void inorder(struct node *root){
    if(root!=NULL){
        inorder(root->left);
        printf("%d %d\n",root->id,root->grade);
        inorder(root->right);
    }
}

void printFormat(struct node *root, struct node *parent, int level, char *childType){
    if(root==NULL) return;

    if(level==1){
        printf("%d %d ",root->id,root->grade);
        if(parent!=NULL){
            printf("(%d %s)",parent->grade,childType);
        }
        printf(" ");
    }
    else if(level>1){
        printFormat(root->left,root,level-1,"L");
        printFormat(root->right,root,level-1,"R");
    }
}

void printTree(struct node *root){
    int h=treeHeight(root);
    int i;
    for(i=1;i<=h;i++){
        printFormat(root,NULL,i,"");
        printf("\n");
    }
}

int main(){
    struct node *tree=NULL;
    int id,grade;
    while(1){
        scanf("%d",&id);
        if(id==-1) break;
        scanf("%d",&grade);
        tree=insert(tree,id,grade);
    }
    inorder(tree);
    printf("\n");
    printTree(tree);
    return 0;
}



#include <stdio.h>
#include <stdlib.h>

struct node{
    int id;
    int grade;
    struct node *left;
    struct node *right;
};

struct node *createNode(int id, int grade){
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    newNode->id = id;
    newNode->grade = grade;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct node *insert(struct node *treeNode, int id, int grade){
    if(treeNode == NULL){
        return createNode(id, grade);
    }
    if(grade < treeNode->grade){
        treeNode->left = insert(treeNode->left, id, grade);
    }
    else{
        treeNode->right = insert(treeNode->right, id, grade);
    }
    return treeNode;
}

int treeHeight(struct node *treeNode){
    if(treeNode == NULL){
        return 0;
    }
    int leftH = treeHeight(treeNode->left);
    int rightH = treeHeight(treeNode->right);
    return (leftH > rightH) ? (leftH + 1) : (rightH + 1);
}

void inorder(struct node *root){
    if(root != NULL){
        inorder(root->left);
        printf("%d %d\n", root->id, root->grade);
        inorder(root->right);
    }
}

void printFormat(struct node *root, struct node *parent, int level, char *childType, int isFirst){
    if(root == NULL) return;

    if(level == 1){
        if (!isFirst){
            printf(" ");  // İlk eleman değilse boşluk ekleyin
        }
        printf("%d %d", root->id, root->grade);
        if(parent != NULL){
            printf(" (%d %s)", parent->grade, childType);
        }
    }
    else if(level > 1){
        printFormat(root->left, root, level-1, "L", isFirst);
        printFormat(root->right, root, level-1, "R", 0);
    }
}

void printTree(struct node *root){
    int h = treeHeight(root);
    for(int i = 1; i <= h; i++){
        printFormat(root, NULL, i, "", 1);
        printf("\n");
    }
}

int main(){
    struct node *tree = NULL;
    int id, grade;
    while(1){
        scanf("%d", &id);
        if(id == -1) break;
        scanf("%d", &grade);
        tree = insert(tree, id, grade);
    }
    inorder(tree);
    printf("\n");
    printTree(tree);
    return 0;
}



//insert this code

void printFormat(struct node *root, struct node *parent, int level, char *childType, int isLast){
    if(root == NULL) return;

    if(level == 1){
        printf("%d %d", root->id, root->grade);
        if(parent != NULL){
            printf(" (%d %s)", parent->grade, childType);
        }
        if (!isLast) {
            printf(" ");
        }
    }
    else if(level > 1){
        if(root->right == NULL) {
            printFormat(root->left, root, level-1, "L", 1);
        } else {
            printFormat(root->left, root, level-1, "L", 0);
            printFormat(root->right, root, level-1, "R", 1);
        }
    }
}


//insert:


void printFormat(struct node *root, struct node *parent, int level, char *childType, int *isFirst) {
    if (root == NULL) return;

    if (level == 1) {
        if (!(*isFirst)) {
            printf(" ");
        }
        printf("%d %d", root->id, root->grade);
        if (parent != NULL) {
            printf(" (%d %s)", parent->grade, childType);
        }
        *isFirst = 0;
    } else if (level > 1) {
        printFormat(root->left, root, level-1, "L", isFirst);
        printFormat(root->right, root, level-1, "R", isFirst);
    }
}

void printTree(struct node *root) {
    int h = treeHeight(root);
    for (int i = 1; i <= h; i++) {
        int isFirst = 1;
        printFormat(root, NULL, i, "", &isFirst);
        printf("\n");
    }
}
