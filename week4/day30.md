# [4주차: 알고리즘 및 시스템 모사 (Algorithms & System)]
## Day 30. 로그 시스템 (Level & Buffer)
- **입력:** `LOG_INFO`, `LOG_ERR` 매크로 호출
- **출력:** `[TIME][LEVEL] File:Line - Message` 형식 출력
- **제약조건:** 로그 레벨에 따른 필터링, 매크로 안에서 `__FILE__`, `__LINE__` 활용.
- **실행결과:**

```c
=== Day 30: Professional Log System ===

[Phase 1] Current Level: INFO
[0 ms][INF] day30_logger.c:75 - System initialized.
[0 ms][WRN] day30_logger.c:76 - Battery low: 15%
[0 ms][ERR] day30_logger.c:80 - Failed to load file: config.ini

>> System Log Level Changed to: DBG (and above)

[Phase 2] Verbose Mode On
[24 ms][DBG] day30_logger.c:88 - Variable i reached limit.
[24 ms][INF] day30_logger.c:89 - Network connected IP: 192.168.0.1
```

---


### 코드

```c

```

### 실행 결과

```bash

```
