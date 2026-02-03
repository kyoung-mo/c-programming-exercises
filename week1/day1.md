# [1주차: 비트 연산과 데이터 표현 (Bitwise & Data)]
## Day 1. 특정 비트 제어 매크로 구현
- **입력:** 32비트 정수 `0x12345678`, 조작할 비트 위치(3), 동작(SET/CLEAR/TOGGLE)
- **출력:** 조작된 16진수 값
- **제약조건:** `<stdint.h>` 사용, 함수가 아닌 매크로로 구현할 것.
- **실행결과:** `SET 3rd bit of 0x... -> 0x...`
    
    ```c
    === Day 1: Bitwise Macro Test === 
    Result   Hex: 0x12345679 | Bin: 0001 0010 0011 0100 0101 0110 0111 1001 
    
    [CLEAR]  Target: Bit 4
    Result   Hex: 0x12345669 | Bin: 0001 0010 0011 0100 0101 0110 0110 1001 
    
    [TOGGLE] Target: Bit 3
    Result   Hex: 0x12345661 | Bin: 0001 0010 0011 0100 0101 0110 0110 0001 
    
    [CHECK]  Bit 3 is currently: 0
    ```

---


### 코드

```c
#include <stdio.h>
#include <stdint.h> 
#define CLR_DEF(n,bit) do{\
        uint32_t f = 0xFFFFFFFF;\
        printf("[CLEAR]  Target: Bit %d\n",bit);    \
        (n&0xFFFFFFFF<<bit+1)|(n&0xFFFFFFFF>>(32-bit));\
        }while(0)
#define TOGGLE_DEF(n,bit) n=n^(1<<0xFFFFFFFF)
#define CHECK_DEF(n,bit)
/*
- **입력:** 32비트 정수 `0x12345678`, 조작할 비트 위치(3), 동작(SET/CLEAR/TOGGLE)
- **출력:** 조작된 16진수 값
- **제약조건:** `<stdint.h>` 사용, 함수가 아닌 매크로로 구현할 것.
- **실행결과:** `SET 3rd bit of 0x... -> 0x...`
*/

void PRT_BIT(uint32_t n){
    uint32_t set_n;
    int cnt=0;

    printf("Result   Hex: 0x%X | Bin: ",n);
    for(int i=31;i>=0;i--){
        set_n=n>>i&1;
        printf("%X",set_n);
        cnt++;

        if(cnt%4==0){
            printf(" ");
        }
    }
    printf("\n\n");
}

uint32_t CLEAR(uint32_t n, int bit){
    uint32_t f = 0xFFFFFFFF;
    printf("[CLEAR]  Target: Bit %d\n",bit);
    n=(n&f<<bit+1)|(n&f>>(32-bit));
    PRT_BIT(n);

    return n;
}

uint32_t TOGGLE(uint32_t n, int bit){
    uint32_t f = 0xFFFFFFFF;
    printf("[TOGGLE]  Target: Bit %d\n",bit);
    n=n^(1<<bit);
    PRT_BIT(n);

    return n;
}

void CHECK(uint32_t n, int bit){
    printf("[CHECK]  Bit %d is currently: %x\n",bit, n&(1<<bit));
}

int main(){

    uint32_t x=0x12345678;

    printf("=== Day 1: Bitwise Macro Test ===\n");

    PRT_BIT(x);
    x=CLEAR(x,4);
    x=TOGGLE(x,3);
    CHECK(x,3);

    return 0;
}
```

### 실행 결과

```bash
=== Day 1: Bitwise Macro Test ===
Result   Hex: 0x12345679 | Bin: 0001 0010 0011 0100 0101 0110 0111 1001

[CLEAR]  Target: Bit 4
Result   Hex: 0x12345669 | Bin: 0001 0010 0011 0100 0101 0110 0110 1001

[TOGGLE] Target: Bit 3
Result   Hex: 0x12345661 | Bin: 0001 0010 0011 0100 0101 0110 0110 0001

[CHECK]  Bit 3 is currently: 0

C:\Users\KCCISTC\source\repos\Project1\x64\Debug\Project1.exe(프로세스 26060)이(가) 0 코드(0x0)와 함께 종료되었습니다.
디버깅이 중지될 때 콘솔을 자동으로 닫으려면 [도구] -> [옵션] -> [디버깅] > [디버깅이 중지되면 자동으로 콘솔 닫기]를 사용하도록 설정합니다.
이 창을 닫으려면 아무 키나 누르세요…
```
