#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
    char data[50];
    int priority;
    struct node *next;
};

struct node *create(char name[50], int pri){
    struct node *NewNode;
    NewNode = (struct node*)malloc(sizeof(struct node));
    if (NewNode == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    strcpy(NewNode->data, name);
    NewNode->priority = pri;
    NewNode->next = NULL;

    return NewNode;
};

struct node *insert(struct node *start, char name[50], int pri) {
    struct node *newNode = create(name, pri);
    struct node *ptr;
    if (start == NULL || pri < start->priority || (pri == start->priority && strcmp(name, start->data) < 0)) {
        newNode->next = start;
        return newNode;
    } else {
        struct node *ptr = start;
        while (ptr->next != NULL && (ptr->next->priority < pri || (ptr->next->priority == pri && strcmp(ptr->next->data, name) < 0))) {
            ptr = ptr->next;
        }
        newNode->next = ptr->next;
        ptr->next = newNode;
        return start;
    }
    return start;
}

int getPriority(char* name) {
    if (strcmp(name, "Annem") == 0 || strcmp(name, "Babam") == 0 || strcmp(name, "Kardesim") == 0 || strcmp(name, "My Mother") == 0 || strcmp(name, "My Father") == 0 || strcmp(name, "My Brother") == 0) {
        return 1;
    } else if (strcmp(name, "Dayim") == 0 || strcmp(name, "Amcam") == 0 || strcmp(name, "Teyzem") == 0 || strcmp(name, "Halam") == 0 || strcmp(name, "My Uncle") == 0 || strcmp(name, "My Aunt") == 0) {
        return 2;
    } else if (strcmp(name, "Isyeri") == 0 || strcmp(name, "Okul") == 0 || strcmp(name, "Workplace") == 0 || strcmp(name, "School") == 0) {
        return 3;
    } else if (strcmp(name, "Arkadasim1") == 0 || strcmp(name, "Arkadasim2") == 0 || strcmp(name, "Arkadasim3") == 0 || strcmp(name, "Arkadasim4") == 0 || strcmp(name, "Arkadasim5") == 0 || strcmp(name, "My Friend1") == 0 || strcmp(name, "My Friend2") == 0 || strcmp(name, "My Friend3") == 0 || strcmp(name, "My Friend4") == 0 || strcmp(name, "My Friend5") == 0) {
        return 4;
    } else if (strcmp(name, "Banka") == 0 || strcmp(name, "Kargo") == 0 || strcmp(name, "Bank") == 0 || strcmp(name, "Cargo") == 0) {
        return 5;
    } else if (strcmp(name, "Reklam") == 0 || strcmp(name, "Advertisement") == 0) {
        return 6;
    }
    return -1;
}
void display(struct node *start){
    struct node *ptr;
    ptr=start;
    if(start==NULL){
        printf("\nqueue is empty");
    }
    else{
        while(ptr!=NULL){
            puts(ptr->data);
            ptr=ptr->next;
        }
    }
}
int main()
{
    struct node *start=NULL;
    char name[50];
    while(1){
        gets(name);
        if (strcmp(name, "-1") == 0) {
            break;
        }
        int priority = getPriority(name);
        if (priority != -1) {
            start = insert(start, name, priority);
        }
    }
    display(start);
    struct node *temp;
    while (start != NULL) {
        temp = start;
        start = start->next;
        free(temp);
    }
    return 0;
}
