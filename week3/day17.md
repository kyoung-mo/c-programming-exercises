# [3주차: 임베디드 필수 자료구조 (Data Structures)]
## Day 17. 비트맵 (Bitmap) 관리자
- **입력:** 관리할 리소스 개수(예: 100개), 할당/해제 요청
- **출력:** 할당된 인덱스 번호
- **제약조건:** `uint8_t` 배열을 비트 단위로 쪼개서 사용 여부 마킹 (1bit = 1resource).
- **실행결과:**

```c
=== Day 17: Bitmap Manager ===

>> Index 0 allocated. (Byte 0, Bit 0 set)
>> Index 1 allocated. (Byte 0, Bit 1 set)
>> Index 2 allocated. (Byte 0, Bit 2 set)
>> Index 3 allocated. (Byte 0, Bit 3 set)
>> Index 4 allocated. (Byte 0, Bit 4 set)
>> Index 5 allocated. (Byte 0, Bit 5 set)
>> Index 6 allocated. (Byte 0, Bit 6 set)
>> Index 7 allocated. (Byte 0, Bit 7 set)
[Bitmap Visual] 11111111 | 00000000 | 0000

Freeing index 2...
>> Index 2 freed. (Byte 0, Bit 2 cleared)
[Bitmap Visual] 11011111 | 00000000 | 0000

Allocating again (expecting index 2)...
>> Index 2 allocated. (Byte 0, Bit 2 set)
[Bitmap Visual] 11111111 | 00000000 | 0000
```

---


### 코드

```c


```

### 실행 결과

```bash

```
