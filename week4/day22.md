# [4주차: 알고리즘 및 시스템 모사 (Algorithms & System)]
## Day 22. 소프트웨어 타이머 (Linked List 기반)
- **입력:** `SetTimer(ID, ms)`, `Tick()` 주기적 호출
- **출력:** 시간 만료 시 콜백 함수 실행
- **제약조건:** 단일 연결 리스트로 남은 시간 순으로 정렬하여 관리(Delta Time 방식).
- **실행결과:** `IDLE ->(Button) -> RUN`

```c
=== Day 22: Software Timer (Delta List) ===

Timer 1 set (10 ms) [Inserted at HEAD]
[Timer List] (ID:1, dt:10, total:10) -> NULL
Timer 2 set (5 ms) [Inserted at HEAD]
[Timer List] (ID:2, dt:5, total:5) -> (ID:1, dt:5, total:10) -> NULL
Timer 3 set (15 ms) [Inserted in List]
[Timer List] (ID:2, dt:5, total:5) -> (ID:1, dt:5, total:10) -> (ID:3, dt:5, total:15) -> NULL

>> Start Ticking...
Tick 1: Rem Head dt: 4
... (생략) ...
Tick 4: Rem Head dt: 1
Tick 5: >> [Event] Timer 2 expired! Action executed.
Rem Head dt: 5
Tick 6: Rem Head dt: 4
... (생략) ...
Tick 9: Rem Head dt: 1
Tick 10: >> [Event] Timer 1 expired! Action executed.
Rem Head dt: 5
Tick 11: Rem Head dt: 4
... (생략) ...
Tick 14: Rem Head dt: 1
Tick 15: >> [Event] Timer 3 expired! Action executed.
All timers cleared.
```

"수많은 타이머를 어떻게 효율적으로 관리할 것인가?"에 대한 임베디드 시스템의 표준 해법입니다.
모든 타이머의 남은 시간을 매번 깎는 방식(O(N))은 타이머가 많아지면 시스템을 느리게 합니다.
대신 **Delta Time(상대 시간)** 방식을 사용하면, 타이머 틱(Tick)마다 **맨 앞의 노드 하나만 깎으면(O(1))** 되므로 성능이 획기적으로 개선됩니다.

---

### 1. 핵심 원리: Delta Time (상대 시간)

타이머를 **"만료될 절대 시간"**이 아니라, **"앞의 타이머가 터지고 나서 기다려야 할 시간"**으로 저장합니다.

- **요청:** A(10ms), B(15ms), C(15ms)
- **저장(Linked List):** `Head -> [A: 10] -> [B: 5] -> [C: 0] -> NULL`
    - A는 10초 뒤 만료.
    - B는 A가 만료된 후 5초 뒤(총 15초) 만료.
    - C는 B가 만료된 후 0초 뒤(즉시, 총 15초) 만료.
---


### 코드

```c

```

### 실행 결과

```bash

```
