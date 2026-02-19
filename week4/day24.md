# [4주차: 알고리즘 및 시스템 모사 (Algorithms & System)] - 구현 덜됐음
## Day 24. 디바운싱 (Debouncing) 알고리즘
- **입력:** 노이즈가 섞인 0/1 입력 배열 (버튼 신호 모사)
- **출력:** 안정화된 출력 값
- **제약조건:** 연속된 N번의 샘플링이 동일할 때만 상태 변경.
- **실행결과:**

```c
=== Day 24: Button Debouncing Logic ===
Condition: 3 consecutive samples required.

Step | Raw Input | Counter | Output (Stable)
-----+-----------+---------+----------------
   1 |     0     |    0    |       0
   2 |     0     |    0    |       0
   3 |     1     |    1    |       0  <-- 노이즈 발생 (카운트 시작)
   4 |     0     |    0    |       0  <-- 다시 0 복귀 (카운트 리셋!)
   5 |     1     |    1    |       0  <-- 진신호 시작
   6 |     1     |    2    |       0
  >> [State Changed] to 1
   7 |     1     |    0    |       1  <-- 3회 연속 성공으로 상태 변경
   8 |     1     |    0    |       1
   9 |     1     |    0    |       1
  10 |     0     |    1    |       1  <-- 노이즈 무시
```

---


### 코드

```c
#include <stdio.h>
/*
- **Day 24. 디바운싱 (Debouncing) 알고리즘**
    - **입력:** 노이즈가 섞인 0/1 입력 배열 (버튼 신호 모사)
    - **출력:** 안정화된 출력 값
    - **제약조건:** 연속된 N번의 샘플링이 동일할 때만 상태 변경.
*/
typedef struct Button_Debouncing{
    int step;
    int raw_input;
    int counter;
    int output;
}Debug;

Debug button_init(Debug* debug){
    debug->step=1;
    debug->raw_input=0;
    debug->counter=0;
    debug->output=0;
}
Debug step_button(Debug* debug, int cnt){
    printf("  Step  | Raw Input | Counter | Output (Stable)\n");
    printf("--------+-----------+---------+----------------\n");
    for(int i=0;i<cnt;i++){
        printf("   %d\t|     %d     |    %d    |       %d\n",debug->step,debug->raw_input,debug->counter,debug->output);
        debug->step++;
    }
}

int main(){
    printf("=== Day 24: Button Debouncing Logic ===\n");
    printf("Condition: 3 consecutive samples required.\n\n");
    
    Debug* debug;
    int count=10;

    button_init(debug);
    step_button(debug,count);
    
    return 0;
}
```

### 실행 결과

```bash
=== Day 24: Button Debouncing Logic ===
Condition: 3 consecutive samples required.

Step  | Raw Input | Counter | Output (Stable)
--------+-----------+---------+----------------
1    |     0     |    0    |       0
2    |     0     |    0    |       0
3    |     0     |    0    |       0
4    |     0     |    0    |       0
5    |     0     |    0    |       0
6    |     0     |    0    |       0
7    |     0     |    0    |       0
8    |     0     |    0    |       0
9    |     0     |    0    |       0
10   |     0     |    0    |       0
[1] + Done                       "/usr/bin/gdb" --interpreter=mi --tty=${DbgTerm} 0<"/tmp/Microsoft-MIEngine-In-4dq21oiv.0ot" 1>"/tmp/Microsoft-MIEngine-Out-4udym13i.uxc”
```
