# [4주차: 알고리즘 및 시스템 모사 (Algorithms & System)]
## Day 29. 간단한 협력형 스케줄러 (Cooperative Scheduler)
- **입력:** 태스크 3개 등록
- **출력:** 태스크가 순차적으로 실행되고 양보(`yield`)하는 로그
- **제약조건:** `setjmp`, `longjmp`를 사용하여 컨텍스트 스위칭 흉내 내기.
- 실행결과: 
```c
=== Day 29: Simple Cooperative Scheduler ===

[Task A] Start working... (Step 1)
  [Task B] Processing Data...
    [Task C] Initialization
[Task A] Resumed working... (Step 2)
  [Task B] Processing Data...
    [Task C] Calculation
[Task A] Start working... (Step 1)
  [Task B] Processing Data...
    [Task C] Finalize
[Task A] Resumed working... (Step 2)

>> Simulation Finished.
```

---


### 코드

```c

```

### 실행 결과

```bash

```
