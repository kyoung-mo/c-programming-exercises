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

```

### 실행 결과

```bash

```
