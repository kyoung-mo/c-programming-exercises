# [4주차: 알고리즘 및 시스템 모사 (Algorithms & System)]
## Day 28. 가변 인자 함수 구현 (my_printf)
- **입력:** 포맷 스트링 `"%d %s"`, 가변 인자
- **출력:** 포맷팅된 문자열 출력
```c
int main() {
    printf("=== Day 28: Custom printf Implementation ===\n\n");

    // Test 1: 정수와 문자열
    my_printf("MyPrint: %d %s\n", 10, "test");

    // Test 2: 16진수와 음수
    my_printf("Hex: 0x%x, Negative: %d\n", 255, -12345);

    // Test 3: 여러 인자 혼합
    my_printf("Result: %d + %d = %d\n", 10, 20, 30);

    return 0;
}
```

- **실행결과:**
```c
=== Day 28: Custom printf Implementation ===

MyPrint: 10 test
Hex: 0xFF, Negative: -12345
Result: 10 + 20 = 30
```

  
---


### 코드

```c

```

### 실행 결과

```bash

```
