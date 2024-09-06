#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node {
    char songName[50];
    int songNumber;
    struct node* prev;
    struct node* next;
};

struct node* createNode(char* songN, int songNum){
   struct node* newNode=(struct node*)malloc(sizeof(struct node));
   strcpy(newNode->songName,songN);
   newNode->songNumber=songNum;
   newNode->prev=NULL;
   newNode->next=NULL;
   return newNode;
}

void appendSong(struct node** head, int songNum,char* songN){
    struct node* newNode=createNode(songN,songNum);
    struct node* temp = *head;
    if(*head== NULL){
        *head=newNode;
        return;
    }
    while(temp->next!=NULL){
        temp=temp->next;
    }
    temp->next=newNode;
    newNode->prev=temp;
}

void printSongs(struct node* head,char start,int advance){
    struct  node* temp;
    if(start=='F'){
        temp=head;
        while(temp!=NULL){
            printf("%s\n",temp->songName);
            for(int i=0;i<advance && temp!=NULL; i++){
                temp=temp->next;
            }
        }
    }
    else if(start=='L'){
        temp=head;
        while(temp->next!=NULL){
            temp=temp->next;
        }
        while (temp!= NULL) {
            printf("%s\n", temp->songName);
            for (int i = 0; i < advance && temp != NULL; i++) {
                temp = temp->prev;
            }
        }
    }
}
int main() {
    struct node* songList=NULL;
    int songNumber=0;
    char songName[50];
    while (1) {
        scanf(" %[^\n]", songName);
        if (strcmp(songName, "-1") == 0) {
            break;
        }
        appendSong(&songList, songNumber++, songName);
    }
    char start;
    int advance;
    scanf(" %c %d",&start,&advance);
    printSongs(songList,start,advance);

    struct node* temp;
    while(songList!=NULL){
        temp=songList;
        songList=songList->next;
        free(temp);
    }
    return 0;
}
