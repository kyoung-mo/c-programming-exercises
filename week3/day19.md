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

```

### 실행 결과

```bash

```
