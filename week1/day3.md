# [1주차: 비트 연산과 데이터 표현 (Bitwise & Data)]
## Day 3. 팩맨 (Packed Data) 파싱
- **입력:** 16비트 정수 (RGB565 포맷: Red 5bit, Green 6bit, Blue 5bit)
- **출력:** R, G, B 각각의 8비트 확장 값 (0~255)
- **제약조건:** 비트 마스킹과 쉬프트 연산 사용.
- **실행결과:**

```c
=== Day 3: Packed Data Parsing (RGB565) ===

Input: 0xFFFF
  [Raw Value] R: 31 (0x1F), G: 63 (0x3F), B: 31 (0x1F)
  [8-bit Ext] R: 248,      G: 252,      B: 248
--------------------------------------------------
Input: 0xF800
  [Raw Value] R: 31 (0x1F), G:  0 (0x00), B:  0 (0x00)
  [8-bit Ext] R: 248,      G:   0,      B:   0
--------------------------------------------------
Input: 0x07E0
  [Raw Value] R:  0 (0x00), G: 63 (0x3F), B:  0 (0x00)
  [8-bit Ext] R:   0,      G: 252,      B:   0
--------------------------------------------------
Input: 0x1234
  [Raw Value] R:  2 (0x02), G: 17 (0x11), B: 20 (0x14)
  [8-bit Ext] R:  16,      G:  68,      B: 160
--------------------------------------------------
```

---


### 코드

```c
#include <stdio.h>
#include <stdint.h>

static inline uint8_t expand5to8(uint8_t v5) {
    // 5-bit(0~31) -> 8-bit(0~255): 상위비트 복제로 근사 확장
    // (v5 << 3) | (v5 >> 2)
    return (uint8_t)((v5 << 3) | (v5 >> 2));
}

static inline uint8_t expand6to8(uint8_t v6) {
    // 6-bit(0~63) -> 8-bit(0~255): 상위비트 복제로 근사 확장
    // (v6 << 2) | (v6 >> 4)
    return (uint8_t)((v6 << 2) | (v6 >> 4));
}

void parse_rgb565(uint16_t packed, uint8_t* r8, uint8_t* g8, uint8_t* b8,
    uint8_t* r_raw, uint8_t* g_raw, uint8_t* b_raw) {
    // RGB565: R(5) G(6) B(5)
    // [15:11] R, [10:5] G, [4:0] B
    uint8_t r5 = (uint8_t)((packed >> 11) & 0x1F);
    uint8_t g6 = (uint8_t)((packed >> 5) & 0x3F);
    uint8_t b5 = (uint8_t)(packed & 0x1F);

    if (r_raw) *r_raw = r5;
    if (g_raw) *g_raw = g6;
    if (b_raw) *b_raw = b5;

    if (r8) *r8 = expand5to8(r5);
    if (g8) *g8 = expand6to8(g6);
    if (b8) *b8 = expand5to8(b5);
}

static void test_one(uint16_t x) {
    uint8_t r5, g6, b5;
    uint8_t r8, g8, b8;

    parse_rgb565(x, &r8, &g8, &b8, &r5, &g6, &b5);

    printf("Input: 0x%04X\n", x);
    printf("[Raw value] R: %u (0x%02X), G: %u (0x%02X), B: %u (0x%02X)\n",
        r5, r5, g6, g6, b5, b5);
    printf("[8-bit Ext] R: %u, G: %u, B: %u\n", r8, g8, b8);
    printf("--------------------------------------------------\n");
}

int main(void) {
    test_one(0xFFFF);
    test_one(0xF800);
    test_one(0x07E0);
    test_one(0x1234);
    return 0;
}

```

### 실행 결과

```bash
Input: 0xFFFF
[Raw value] R: 31 (0x1F), G: 63 (0x3F), B: 31 (0x1F)
[8-bit Ext] R: 255, G: 255, B: 255
--------------------------------------------------
Input: 0xF800
[Raw value] R: 31 (0x1F), G: 0 (0x00), B: 0 (0x00)
[8-bit Ext] R: 255, G: 0, B: 0
--------------------------------------------------
Input: 0x07E0
[Raw value] R: 0 (0x00), G: 63 (0x3F), B: 0 (0x00)
[8-bit Ext] R: 0, G: 255, B: 0
--------------------------------------------------
Input: 0x1234
[Raw value] R: 2 (0x02), G: 17 (0x11), B: 20 (0x14)
[8-bit Ext] R: 16, G: 69, B: 165
--------------------------------------------------

C:\Users\KCCISTC\source\repos\260114\x64\Debug\260114.exe(프로세스 9244)이(가) 0 코드(0x0)와 함께 종료되었습니다.
디버깅이 중지될 때 콘솔을 자동으로 닫으려면 [도구] -> [옵션] -> [디버깅] > [디버깅이 중지되면 자동으로 콘솔 닫기]를 사용하도록 설정합니다.
이 창을 닫으려면 아무 키나 누르세요…
```
