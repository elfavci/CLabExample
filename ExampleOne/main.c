#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 15

void createArray(char arr[SIZE][SIZE]) {
    char ch;
    int validInput = 0;

    while (!validInput) {
        validInput = 1;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                scanf(" %c", &ch);
                if (!isupper(ch)) {
                    validInput = 0;
                }
                arr[i][j] = ch;
            }
        }
        if (!validInput) {
            printf("Please enter only uppercase letters. Re-enter the whole array:\n");
        }
    }
}

void printArray(char arr[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c", arr[i][j]);
        }
        printf("\n");
    }
}

int HorizontalSearch(char arr[SIZE][SIZE],char *str){
    int len=strlen(str);
    //horizontal flat search
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<=SIZE-len;j++){
            int k;
            for(k=0;k<len;k++){
                if(arr[i][j+k]!=str[k]){
                    break;
                }
            }
            if(k==len){
                markFoundWord(arr, i, j, 0, 1, len);
                return 1;
            }
        }
    }
    //horizontal reverse search
    for(int i=0;i<SIZE;i++){
        for(int j=SIZE-1;j>=len-1;j--){
            int k;
            for(k=0;k<len;k++){
                if(arr[i][j-k]!=str[k]){
                    break;
                }
            }
             if (k == len) {
                markFoundWord(arr, i, j, 0, -1, len);
                return 1;
            }
        }
    }
    return 0;
}

int VerticalSearch(char arr[SIZE][SIZE],char *str){
    int len=strlen(str);
    //vertical flat search
    for(int i=0;i<=SIZE-len;i++){
        for(int j=0;j<SIZE;j++){
            int k;
            for(k=0;k<len;k++){
                if(arr[i+k][j]!=str[k]){
                    break;
                }
            }
            if(k==len){
                markFoundWord(arr, i, j, 1, 0, len);
                return 1;
            }
        }
    }
    //vertical reverse search
    for(int i=SIZE-1;i>=len-1;i--){
        for(int j=0;j<SIZE;j++){
            int k;
            for(k=0;k<len;k++){
                if(arr[i-k][j]!=str[k]){
                    break;
                }
            }
             if (k == len) {
                markFoundWord(arr, i, j, -1, 0, len);
                return 1;
            }
        }
    }
    return 0;
}

int DiagonalSearch(char arr[SIZE][SIZE],char *str){
    int len=strlen(str);
    //from top left to bottom right
    for(int i=0;i<=SIZE-len;i++){
        for(int j=0;j<=SIZE-len;j++){
            int k;
            for(k=0;k<len;k++){
                if(arr[i+k][j+k]!=str[k]){
                    break;
                }
            }
            if (k == len) {
                markFoundWord(arr, i, j, 1, 1, len);
                return 1;
            }
        }
    }
    //from top right to bottom left
    for(int i=0;i<SIZE-len;i++){
        for(int j=SIZE-1;j>=len-1;j--){
            int k;
            for(k=0;k<len;k++){
                if(arr[i+k][j-k]!=str[k]){
                    break;
                }
            }
            if (k == len) {
                markFoundWord(arr, i, j, 1, -1, len);
                return 1;
            }
        }
    }
    //from bottom left to top right
    for(int i=SIZE-1;i>=len-1;i--){
        for(int j=0;j<SIZE-len;j++){
            int k;
            for(k=0;k<len;k++){
                if(arr[i-k][j+k]!=str[k]){
                    break;
                }
            }
            if (k == len) {
                markFoundWord(arr, i, j, -1, 1, len);
                return 1;
            }
        }
    }
    //from bottom right to top left
    for(int i=SIZE-1;i>=len-1;i--){
        for(int j=SIZE-1;j>=len-1;j--){
            int k;
            for(k=0;k<len;k++){
                if(arr[i-k][j-k]!=str[k]){
                    break;
                }
            }
            if (k == len) {
                markFoundWord(arr, i, j, -1, -1, len);
                return 1;
            }
        }
    }
    return 0;
}

void markFoundWord(char arr[SIZE][SIZE], int x, int y, int dx, int dy, int len) {
    char tempArr[SIZE][SIZE];

    // Fill the temporary array with asterisks
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            tempArr[i][j] = '*';
        }
    }
    // Copy the found word into the temporary array
    for (int i = 0; i < len; i++) {
        tempArr[x + i * dx][y + i * dy] = arr[x + i * dx][y + i * dy];
    }
    // Copy the temporary array back into the original array
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            arr[i][j] = tempArr[i][j];
        }
    }
}

void markNotFound(char arr[SIZE][SIZE]){
    // Fill the temporary array with asterisks
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            arr[i][j] = '*';
        }
    }
}

int main()
{
    char array[SIZE][SIZE];
    createArray(array);
    char str[SIZE];
    int flag=0;
    while (!flag) {
        scanf(" %s", &str);
        flag=1;
        for(int i=0;str[i]!='\0';i++){
            if(!isupper(str[i])){
                flag=0;
                printf("Please enter only uppercase letters.\n");
                break;
            }

        }
    }
     if (!HorizontalSearch(array, str) && !VerticalSearch(array, str) && !DiagonalSearch(array, str)) {
        markNotFound(array);
    }

    printf("\n");
    printArray(array);

    return 0;
}

