# [3주차: 임베디드 필수 자료구조 (Data Structures)]
## Day 20. 희소 행렬(Sparse Matrix) 압축
- **입력:** 0이 대부분인 2차원 배열
- **출력:** (Row, Col, Value) 구조체 배열로 변환된 데이터
- **제약조건:** 메모리 사용량 비교 출력.
- **실행결과:**

```c
=== Day 20: Sparse Matrix Compression ===

--- Compressed Data (Row, Col, Val) ---
Index 0: (0, 1, 5)
Index 1: (2, 3, 8)
Index 2: (4, 0, 2)
Index 3: (4, 5, 9)

[Memory Usage Analysis]
Original Matrix Size : 400 bytes (100 x 4 ints)
Compressed Data Size : 48 bytes (4 elements x3 x 4 bytes)
>> Compression Ratio : 12.0% of original size
```
<img width="1400" height="600" alt="image" src="https://github.com/user-attachments/assets/a4b437ab-2364-4f91-98b0-b200acbb7504" />


---


### 코드

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ROW 100
#define COL 4
#define MAX_SIZE 50

int index_count;

typedef struct Matrix{ // 출력에 사용
    int row;
    int col;
    int value;
}Sparse_Matrix;

int sparse_matrix[ROW][COL]={0};
//void print_matrix();
void input_value(int row, int col, int value);
int save_compressed_matrix();
void memory_analysis(int index);

int main(){
    int index;
    printf("=== Day 20: Sparse Matrix Compression ===\n\n");
    // print_matrix();
    input_value(0,1,5);
    input_value(2,3,8);
    input_value(4,0,2);
    input_value(4,5,9); // 입력은 끝
    // print_matrix(); 

    printf("--- Compressed Data (Row, Col, Val) ---\n"); // 출력 관련 시작
    index = save_compressed_matrix();

    printf("[Memory Usage Analysis]\n");
    memory_analysis(index);    

    return 0;
}

void print_matrix(){
    for(int i=0;i<ROW;i++){
        for(int j=0;j<COL;j++){
            printf("%d ",sparse_matrix[i][j]);
        }
        printf("\n");
    }
}

void input_value(int row, int col, int value){
    sparse_matrix[row][col]=value;
}

int save_compressed_matrix(){

    Sparse_Matrix* comp_matrix[MAX_SIZE];
    for(int i=0;i<MAX_SIZE;i++){
    comp_matrix[i]=(Sparse_Matrix*)malloc(sizeof(Sparse_Matrix));
    }

    for(int i=0;i<ROW;i++){
        for(int j=0;j<COL;j++){
            int value=sparse_matrix[i][j];

            if(value!=0){
                comp_matrix[index_count]->row=i;
                comp_matrix[index_count]->col=j;
                comp_matrix[index_count]->value=value;
                index_count++;
            }
        }
    }

    for(int i=0;i<index_count;i++){
        printf("[index %d] row = %d, col = %d, value = %d\n",i,comp_matrix[i]->row,comp_matrix[i]->col,comp_matrix[i]->value);
    }
    printf("\n");

    for(int i=MAX_SIZE-1;i>=0;i--){
        free(comp_matrix[i]);
    }

    return index_count;
}

void memory_analysis(int index){
    printf("Original Matrix Size : %d bytes (%d x %d x 4 bytes)\n",sizeof(int)*ROW*COL,ROW,COL);
    printf("Compressed Data Size : %d bytes (%d elements x 3 x %d bytes)\n",3*sizeof(int)*index,index,sizeof(int));
    printf(">> Compression Ratio : %.1lf%% of original size\n",(3*(double)index)/(ROW*COL)*100);
}
```

### 실행 결과

```bash
=== Day 20: Sparse Matrix Compression ===

--- Compressed Data (Row, Col, Val) ---
[index 0] row = 0, col = 1, value = 5
[index 1] row = 2, col = 3, value = 8
[index 2] row = 4, col = 0, value = 2
[index 3] row = 5, col = 1, value = 9

[Memory Usage Analysis]
Original Matrix Size : 1600 bytes (100 x 4 x 4 bytes)
Compressed Data Size : 48 bytes (4 elements x 3 x 4 bytes)
>> Compression Ratio : 3.0% of original size
[1] + Done                       "/usr/bin/gdb" --interpreter=mi --tty=${DbgTerm} 0<"/tmp/Microsoft-MIEngine-In-wlqtgxhg.evm" 1>"/tmp/Microsoft-MIEngine-Out-i2pvcsxw.0v1”
```
