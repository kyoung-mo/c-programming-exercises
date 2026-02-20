# [4주차: 알고리즘 및 시스템 모사 (Algorithms & System)]
## Day 25. 이동 평균 필터 (Moving Average)
- **입력:** 센서 노이즈 데이터 스트림
- **출력:** 필터링된 값
- **제약조건:** 최근 N개의 데이터를 저장하는 윈도우 버퍼 사용, 매번 합계 다시 계산하지 말고 최적화(Sliding Window).
- **실행결과:**

```c
=== Day 25: Moving Average Filter (Sliding Window) ===
Window Size: 5

Step | Raw Input | Filtered Output
-----+-----------+----------------
   1 |    20.0   |       20.0  (1개 평균)
   2 |    22.0   |       21.0  (2개 평균)
   3 |    18.0   |       20.0  (3개 평균: 20+22+18 / 3)
   4 |    25.0   |       21.2
   5 |    15.0   |       20.0  (5개 꽉 참)
   6 |    20.0   |       20.0  (20.0이 들어오고, 맨 처음 20.0이 빠짐)
   7 |    21.0   |       19.8  (21.0이 들어오고, 22.0이 빠짐 -> 평균 하락)
   8 |    19.0   |       20.0
   9 |    20.5   |       19.1
  10 |    20.0   |       20.1
```

<img width="1024" height="559" alt="image" src="https://github.com/user-attachments/assets/fd2c2c91-9771-4f14-b105-fd817008c98d" />

---


### 코드

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* 
  Day 25. 이동 평균 필터 (Moving Average)
- **입력:** 센서 노이즈 데이터 스트림
- **출력:** 필터링된 값
- **제약조건:** 최근 N개의 데이터를 저장하는 윈도우 버퍼 사용, 매번 합계 다시 계산하지 말고 최적화(Sliding Window).
*/
typedef struct Sliding_Window{
    int step;
    double* row_input;
    double* filtered_output;
}Filter;

void filter_init(Filter* init_filter,double* input){
    init_filter->step=1;
    init_filter->row_input=(double*)malloc(sizeof(double)*10);
    for(int i=0;i<10;i++){
        init_filter->row_input[i]=input[i];
    }
    init_filter->filtered_output=(double*)malloc(sizeof(double)*5);
}

void moving_average_filter(Filter* filter){
    double sum_input=0;
    int cnt=1;
    printf("Step | Raw Input | Filtered Output\n");
    printf("-----+-----------+----------------\n");
    for(int i=0;i<10;i++){
        if(i<5){
            sum_input += filter->row_input[i];
        }
        else{
            sum_input += filter->row_input[i];
            sum_input -= filter->row_input[i-5];
            cnt=5;
        }
        filter->filtered_output[i]=sum_input/cnt++;
        printf("   %d |    %.1lf   |       %.1lf\n",filter->step++, filter->row_input[i], filter->filtered_output[i]);    
    } 
}


int main(){
    Filter* filter=(Filter*)malloc(sizeof(Filter));
    int buffer_size=5;
    double input[10] = {20.0,22.0,18.0,25.0,15.0,20.0,21.0,19.0,20.5,20.0};

    printf("=== Day 25: Moving Average Filter (Sliding Window) ===\n");
    printf("Window Size: %d\n\n",buffer_size);

    filter_init(filter, &input);
    moving_average_filter(filter);

    return 0;
}
```

### 실행 결과

```bash
=== Day 25: Moving Average Filter (Sliding Window) ===
Window Size: 5

Step | Raw Input | Filtered Output
-----+-----------+----------------
1 |    20.0   |       20.0
2 |    22.0   |       21.0
3 |    18.0   |       20.0
4 |    25.0   |       21.2
5 |    15.0   |       20.0
6 |    20.0   |       20.0
7 |    21.0   |       19.8
8 |    19.0   |       20.0
9 |    20.5   |       19.1
10 |    20.0   |       20.1
[1] + Done                       "/usr/bin/gdb" --interpreter=mi --tty=${DbgTerm} 0<"/tmp/Microsoft-MIEngine-In-l3ty5ddy.kc3" 1>"/tmp/Microsoft-MIEngine-Out-4bsbzvlr.2vf”
```
