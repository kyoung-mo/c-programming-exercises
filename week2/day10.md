# [2주차: 포인터와 메모리 관리 (Memory & Pointers)]
- **입력:** 행(row) 수, 열(col) 수
    
    ```c
    === Day 10: Dynamic 2D Array Allocation ===
    
    Generated Matrix (3x4):
     1  2  3  4
     5  6  7  8
     9 10 11 12
    
    >> Memory successfully freed.
    ```
    
- **출력:** 연속된 메모리 공간을 갖는 2차원 배열 구조
- **제약조건:** `malloc` 호출 횟수를 최소화할 것 (데이터 영역은 한 번에 할당).
- **실행결과:**
- 참고
    
    리눅스에서 valgrind를 인스톨하고 메모리 leak를 검사하면 다음과 같은 결과가 나온다. 
    
    마지막 메모리할당한것을 해제 하지 않음. 
    
    ```c
    $ sudo apt install valgrind
    
    $ valgrind ./a.out
    ==1282== Memcheck, a memory error detector
    ==1282== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
    ==1282== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
    ==1282== Command: ./a.out
    ==1282==
    === Day 10: Dynamic 2D Array Allocation ===
    
    Generated Matrix (3x4):
     1  2  3  4
     5  6  7  8
     9 10 11 12
    
    >> Memory successfully freed.
    ==1282==
    ==1282== HEAP SUMMARY:
    ==1282==     in use at exit: 24 bytes in 1 blocks
    ==1282==   total heap usage: 5 allocs, 4 frees, 1,096 bytes allocated
    ==1282==
    ==1282== LEAK SUMMARY:
    ==1282==    definitely lost: 24 bytes in 1 blocks
    ==1282==    indirectly lost: 0 bytes in 0 blocks
    ==1282==      possibly lost: 0 bytes in 0 blocks
    ==1282==    still reachable: 0 bytes in 0 blocks
    ==1282==         suppressed: 0 bytes in 0 blocks
    ==1282== Rerun with --leak-check=full to see details of leaked memory
    ==1282==
    ==1282== For lists of detected and suppressed errors, rerun with: -s
    ```
---


### 코드

```c
#include <stdio.h>
#include <stdint.h>

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
```

### 실행 결과

```bash
mo@DESKTOP-HMRIDMH:~/Intel_AI_SW_Academy_9th/red_drug/week2$ valgrind ./day10
==23033== Memcheck, a memory error detector
==23033== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==23033== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==23033== Command: ./day10
==23033==
=== Day 10: Dynamic 2D Array Allocation ===

Generated Matrix (3x4):
1  2  3  4
5  6  7  8
9 10 11 12
>> Memory free failed.
==23033==
==23033== HEAP SUMMARY:
==23033==     in use at exit: 24 bytes in 1 blocks
==23033==   total heap usage: 5 allocs, 4 frees, 1,096 bytes allocated
==23033==
==23033== LEAK SUMMARY:
==23033==    definitely lost: 24 bytes in 1 blocks
==23033==    indirectly lost: 0 bytes in 0 blocks
==23033==      possibly lost: 0 bytes in 0 blocks
==23033==    still reachable: 0 bytes in 0 blocks
==23033==         suppressed: 0 bytes in 0 blocks
==23033== Rerun with --leak-check=full to see details of leaked memory
==23033==
==23033== For lists of detected and suppressed errors, rerun with: -s
==23033== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
