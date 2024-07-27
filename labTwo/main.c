#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void blobInput(char **arr,int a,int b){
    int x,y;
    while(true){
        scanf("%d", &x);
        if(x==-1){
            break;
        }
        else{
            scanf("%d", &y);
            for(int i=0;i<a;i++){
                for(int j=0;j<b;j++){
                    if(x==i && y==j){
                        arr[i][j]='*';
                    }
                }
            }
        }
    }
}

int depthFsearch(char **arr,bool **visit,int x,int y,int a,int b){
    if(x<0 || x>=a || y<0 || y>=b || arr[x][y]!='*' || visit[x][y]){
        return 0;
    }
    visit[x][y]=true;
    int count=1;

    //Check 8 neighbors
    //up left x-1, y-1
    count+=depthFsearch(arr,visit,x-1,y-1,a,b);
    //up x-1, y
    count+=depthFsearch(arr,visit,x-1,y,a,b);
    //up right x-1, y+1
     count += depthFsearch(arr, visit, x-1, y+1, a, b);
     //left x, y-1
     count += depthFsearch(arr, visit, x, y-1, a, b);
     //right x, y+1
     count += depthFsearch(arr, visit, x, y+1, a, b);
     //down left x+1, y-1
     count += depthFsearch(arr, visit, x+1, y-1, a, b);
     //down x+1, y
     count += depthFsearch(arr, visit, x+1, y, a, b);
     //down right x+1, y+1
      count += depthFsearch(arr, visit, x+1, y+1, a, b);

      return count;
}

void findBlobs(char **arr,bool **visit,int a, int b){
    int *blobCounts = (int *)malloc(a * b * sizeof(int));
    int blobCount = 0;

   // Find blobs for each cell
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            if (arr[i][j] == '*' && !visit[i][j]) {
                int count = depthFsearch(arr, visit, i, j, a, b);
                if (count > 0) {
                    blobCounts[blobCount++] = count;
                }
            }
        }
    }
    //Sort blob sizes in ascending order
    for(int i=0;i<blobCount-1;i++){
        for(int j=i+1;j<blobCount;j++){
            if (blobCounts[i] > blobCounts[j]) {
                int temp=blobCounts[i];
                blobCounts[i]=blobCounts[j];
                blobCounts[j]=temp;
            }
        }
    }
    printf("%d ",blobCount);
    for(int i=0;i<blobCount;i++){
        printf("%d ",blobCounts[i]);
    }

    free(blobCounts);
}
int main()
{
    int a,b;
    scanf("%d %d",&a,&b);

    char **arr=(char**)malloc(a*sizeof(char*));
    bool **visited=(bool **)malloc(a*sizeof(bool *));
    for(int i=0;i<a;i++){
        arr[i]=(char*)malloc(b*sizeof(char));
        visited[i]=(bool *)malloc(b*sizeof(bool));
        for(int j=0;j<b;j++){
            arr[i][j]=' ';
            visited[i][j]=false;
        }
    }
    blobInput(arr,a,b);
    findBlobs(arr,visited,a,b);
    for(int i=0;i<a;i++){
        free(arr[i]);
        free(visited[i]);
    }
    free(arr);
    free(visited);

    return 0;
}
