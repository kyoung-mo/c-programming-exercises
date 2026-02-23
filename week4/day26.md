# [4주차: 알고리즘 및 시스템 모사 (Algorithms & System)]
## Day 26. 생산자-소비자 (Producer-Consumer) 시뮬레이션
- **입력:** 랜덤한 생산 및 소비 속도
- **출력:** 버퍼 상태 및 데이터 처리 로그
- **제약조건:** 뮤텍스/세마포어 개념을 `volatile` 플래그로 단순화하여 모사.
- **실행결과:**

```c
=== Day 26: Producer-Consumer Simulation ===
Buffer Size: 5

[PROD] Produced Item 1 (Head: 1, Count: 1)
[PROD] Produced Item 2 (Head: 2, Count: 2)
[CONS] Consumed Item 1 (Tail: 1, Count: 1)
[PROD] Produced Item 3 (Head: 3, Count: 2)
[PROD] Produced Item 4 (Head: 4, Count: 3)
[PROD] Produced Item 5 (Head: 0, Count: 4)
[PROD] Produced Item 6 (Head: 1, Count: 5)
  >> [Buffer Full!] Producer waits... (Count: 5)  <-- 꽉 참!
  >> [Buffer Full!] Producer waits... (Count: 5)
[CONS] Consumed Item 2 (Tail: 2, Count: 4)        <-- 소비자가 공간 확보
[PROD] Produced Item 7 (Head: 2, Count: 5)        <-- 다시 생산 가능
[CONS] Consumed Item 3 (Tail: 3, Count: 4)
...
```

---


### 코드

```c
#include <stdio.h>
/* 
Day 26. 생산자-소비자 (Producer-Consumer) 시뮬레이션
- **입력:** 랜덤한 생산 및 소비 속도
- **출력:** 버퍼 상태 및 데이터 처리 로그
- **제약조건:** 뮤텍스/세마포어 개념을 `volatile` 플래그로 단순화하여 모사.
- **실행결과:**
*/
typedef struct BUFFER{
    int head;
    int tail;
    int count;
    volatile int buffer_locked;
}PCSimulation;

void simulation_init(PCSimulation* simul_init, int buf_size){
    simul_init->head=0;
    simul_init->tail=0;
    simul_init->count=0;
    simul_init->buffer_locked=0;
}

void producer_consumer_simulation(PCSimulation* simul, int* input, int input_size){
    int produced_item=0;
    int consumed_item=0;
    simul->count=0;
    for(int i=0;i<input_size;i++){
        
        if(input[i]==1){
            simul->count++;
            if(simul->count>5&&simul->buffer_locked==0){
                simul->buffer_locked=1;
                simul->count--;
                simul->buffer_locked=0;
                printf("  >> [Buffer Full!] Producer waits... (Count: %d)\n",simul->count);
                continue;
            }
            if(simul->head==4&&simul->buffer_locked==0){
                simul->buffer_locked=1;
                simul->head=-1;
                simul->buffer_locked=0;
            }
            printf("[PROD] Produced Item %d (Head: %d, Count: %d)\n",++produced_item,++simul->head,simul->count);
        }
        else if(input[i]==0&&simul->buffer_locked==0){
            simul->buffer_locked=1;
            simul->count--;
            simul->buffer_locked=0;
            printf("[CONS] Consumed Item %d (Tail: %d, Count: %d)\n",++consumed_item,++simul->tail,simul->count);
        }
        
    }
}

int main(){
    PCSimulation* simulation=(PCSimulation*)malloc(sizeof(PCSimulation));
    int buffer_size=5;
    int input_flag[]={1,1,0,1,1,1,1,1,1,0,1,0};

    printf("=== Day 26: Producer-Consumer Simulation ===\n");
    printf("Buffer Size: %d\n\n",buffer_size);

    simulation_init(simulation, buffer_size);
    producer_consumer_simulation(simulation, &input_flag,12);

    return 0;
}
```

### 실행 결과

```bash
=== Day 26: Producer-Consumer Simulation ===
Buffer Size: 5

[PROD] Produced Item 1 (Head: 1, Count: 1)
[PROD] Produced Item 2 (Head: 2, Count: 2)
[CONS] Consumed Item 1 (Tail: 1, Count: 1)
[PROD] Produced Item 3 (Head: 3, Count: 2)
[PROD] Produced Item 4 (Head: 4, Count: 3)
[PROD] Produced Item 5 (Head: 0, Count: 4)
[PROD] Produced Item 6 (Head: 1, Count: 5)
>> [Buffer Full!] Producer waits... (Count: 5)
>> [Buffer Full!] Producer waits... (Count: 5)
[CONS] Consumed Item 2 (Tail: 2, Count: 4)
[PROD] Produced Item 7 (Head: 2, Count: 5)
[CONS] Consumed Item 3 (Tail: 3, Count: 4)
[1] + Done                       "/usr/bin/gdb" --interpreter=mi --tty=${DbgTerm} 0<"/tmp/Microsoft-MIEngine-In-h1dqhkmh.kvp" 1>"/tmp/Microsoft-MIEngine-Out-mnqicgp2.4tp”
```
