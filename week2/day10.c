#include <stdio.h>
#include <stdint.h>

void prt_matrix(int row, int col);

int main(){
    printf("=== Day 10: Dynamic 2D Array Allocation ===\n\n");

    int row = 3, col = 4;
    int **arr = (int**)malloc(sizeof(int*)*row);

    printf("Generated Matrix (%dx%d):\n",row,col);

    for(int i=0;i<row;i++){
        arr[i] = (int*)malloc(sizeof(int) * col);
    }

    for(int i = 0;i<row;i++){
        for(int j=0;j<col;j++){
            arr[i][j] = i*col+j;
            printf("%2d ",arr[i][j]+1);
        }
        printf("\n");
    }

    for(int i =0;i<row;i++){
        free(arr[i]);
    }
    //free(arr);
    //arr=NULL;

    if(arr == NULL){
        printf(">> Memory successfully freed.\n");
    }
    else if(arr!=NULL){
        printf(">> Memory free failed.\n");
    }
    return 0;
}