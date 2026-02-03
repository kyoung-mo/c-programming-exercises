# [1주차: 비트 연산과 데이터 표현 (Bitwise & Data)]
## Day 2. Endianness 변환 함수 (Network to Host)
- **입력:** 32비트 정수 `0x12345678` (Big Endian 가정 데이터)
- **출력:** 실행 시스템의 Endian에 맞춰 변환된 값
- **제약조건:** 시스템의 Endian을 런타임에 판별하여 동작할 것. 비트 연산만 사용.
- **실행결과:**

```c
=== Day 2: Endianness Conversion ===
Received Data (Hex): 0x12345678

[System Check] This system is Little Endian.
 -> Need to swap bytes to match Host Order.

Original (Network): 0x12345678
Converted (Host)  : 0x78563412
Memory Dump: [12] [34] [56] [78] (Low Addr -> High Addr)
```

---


### 코드

```c
#include <stdio.h>
#include <stdint.h>

int is_little_endian(void) {
    uint16_t x = 0x0001;
    return *((uint8_t*)&x);
}

uint32_t swap_endian32(uint32_t v) {
    return ((v & 0x000000FF) << 24) |
        ((v & 0x0000FF00) << 8) |
        ((v & 0x00FF0000) >> 8) |
        ((v & 0xFF000000) >> 24);
}

void dump_memory(uint32_t v) {
    uint8_t* p = (uint8_t*)&v;

    printf("Memory Dump: ");
    for (int i = 0; i < 4; i++) {
        printf("[%02X] ", p[i]);
    }
    printf("(Low Addr -> High Addr)\n");
}

int main(void) {
    uint32_t net_data = 0x12345678;
    uint32_t host_data;

    printf("=== Day 2: Endianness Conversion ===\n");
    printf("Received Data (Hex): 0x%08X\n\n", net_data);

    if (is_little_endian()) {
        printf("[System Check] This system is Little Endian.\n");
        printf(" -> Need to swap bytes to match Host Order.\n\n");
        host_data = swap_endian32(net_data);
    }
    else {
        printf("[System Check] This system is Big Endian.\n");
        printf(" -> No conversion needed.\n\n");
        host_data = net_data;
    }

    printf("Original (Network): 0x%08X\n", net_data);
    printf("Converted (Host)  : 0x%08X\n", host_data);

    dump_memory(net_data);

    return 0;
}

```

### 실행 결과

```bash
=== Day 2: Endianness Conversion ===
Received Data (Hex): 0x12345678

[System Check] This system is Little Endian.
-> Need to swap bytes to match Host Order.

Original (Network): 0x12345678
Converted (Host)  : 0x78563412
Memory Dump: [78] [56] [34] [12] (Low Addr -> High Addr)

C:\Users\KCCISTC\source\repos\Project1\x64\Debug\Project1.exe(프로세스 17152)이(가) 0 코드(0x0)와 함께 종료되었습니다.
디버깅이 중지될 때 콘솔을 자동으로 닫으려면 [도구] -> [옵션] -> [디버깅] > [디버깅이 중지되면 자동으로 콘솔 닫기]를 사용하도록 설정합니다.
이 창을 닫으려면 아무 키나 누르세요…
```
