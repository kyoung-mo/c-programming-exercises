# [3주차: 임베디드 필수 자료구조 (Data Structures)]
## Day 19. 스택 오버플로우 감지 (Canary)
- **입력:** 재귀 함수 깊게 호출
- **출력:** 스택 한계 도달 시 경고 메시지
- **제약조건:** 스택 영역 끝에 특정 패턴(Canary)을 심고 주기적으로 검사.
- **실행결과:**

```c
=== Day 19: Stack Overflow Detection (Canary Simulation) ===
Stack Base Address: 0x7ffc06e480d4
Soft Limit: 4096 bytes

Current Stack Usage: 33 bytes
Current Stack Usage: 1041 bytes
Current Stack Usage: 2049 bytes
Current Stack Usage: 2097 bytes
Current Stack Usage: 3105 bytes
Current Stack Usage: 4113 bytes

[!!! WARNING !!!] Stack Overflow Detected!
Limit: 4096, Used: 4113

>> System survived. Returned safely to main.
```

---


### 코드

```c
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define SOFT_LIMIT 4096
#define CANARY_VALUE 0xDEADBEEF

static uint8_t *base_ptr = NULL;

int stack_usage(){
    volatile uint8_t buffer[512];
    volatile uint32_t canary = CANARY_VALUE;
    uint8_t local;

    int used = (int)(base_ptr - &local);
    if(used < 0) used = -used;

    printf("Current Stack Usage: %d bytes\n", used);

    if(canary != CANARY_VALUE){
        printf("[CANARY CORRUPTED!] Stack integrity compromised!\n");
    }

    if(used >= SOFT_LIMIT){
        return used;
    }

    return stack_usage();
}

int main(){

    int used_byte=0;
    uint8_t start_address;
    base_ptr = &start_address;

    printf("=== Day 19: Stack Overflow Detection (Canary Simulation) ===\n");
    printf("Stack Base Address: %p\n",(void*)&start_address);
    printf("Soft Limit: %d bytes\n\n",SOFT_LIMIT);

    while(1){
        used_byte = stack_usage();
        if(used_byte>=SOFT_LIMIT) {
            printf("[!!! WARNING !!!] Stack Overflow Detected!\n");
            printf("Limit: %d, Used: %d\n\n",SOFT_LIMIT, used_byte);

            printf(">> System survived. Returned safely to main.\n");
            break;
        }
    }

    return 0;
}
```

### 실행 결과

```bash
=== Day 19: Stack Overflow Detection (Canary Simulation) ===
Stack Base Address: 0x7fffffffdd03
Soft Limit: 4096 bytes

Current Stack Usage: 556 bytes
Current Stack Usage: 1116 bytes
Current Stack Usage: 1676 bytes
Current Stack Usage: 2236 bytes
Current Stack Usage: 2796 bytes
Current Stack Usage: 3356 bytes
Current Stack Usage: 3916 bytes
Current Stack Usage: 4476 bytes
[!!! WARNING !!!] Stack Overflow Detected!
Limit: 4096, Used: 4476

>> System survived. Returned safely to main.
[1] + Done                       "/usr/bin/gdb" --interpreter=mi --tty=${DbgTerm} 0<"/tmp/Microsoft-MIEngine-In-mt04k1rc.2fq" 1>"/tmp/Microsoft-MIEngine-Out-2xf0jfqj.gxo”
```
