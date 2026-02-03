# [1주차: 비트 연산과 데이터 표현 (Bitwise & Data)]
## Day 6. 원형 비트 시프트 (Circular Shift/Rotate)
- **입력:** 32비트 정수, 이동할 비트 수 `n`, 방향(Left/Right)
- **출력:** 회전된 결과값
- **제약조건:** 버려지는 비트가 반대편으로 채워져야 함.
- **실행결과:** ROL ⇒ Rotation Left, ROR ⇒ Rotation Right
- 

```c
=== Day 6: Circular Shift (Rotate) ===

[Init]   Hex: 0xF0000000
         Bin: 1111 0000 0000 0000 0000 0000 0000 0000 

[ROL 4]  Hex: 0x0000000F
         Bin: 0000 0000 0000 0000 0000 0000 0000 1111 
         (MSB bits moved to LSB)

[ROR 4]  Hex: 0xF0000000
         Bin: 1111 0000 0000 0000 0000 0000 0000 0000 
         (Restored to original)

[Test 2] Data: 0x12345678 -> ROR 8 -> 0x78123456
```

---


### 코드

```c
#include <stdio.h>
#include <stdint.h>

/*
- **입력:** 32비트 정수, 이동할 비트 수 `n`, 방향(Left/Right)
- **출력:** 회전된 결과값
- **제약조건:** 버려지는 비트가 반대편으로 채워져야 함.
- **실행결과:** ROL ⇒ Rotation Left, ROR ⇒ Rotation Right
*/

void print_bits(uint32_t k){
    printf("\tHex: 0x%08X",k);
    printf("\n\tBin: ");
    int count=0;
    for(int i=31;i>=0;i--){ // 1111 0000 0000 0000 0000 0000 0000 0000
        printf("%x",(k>>i)&(0x00000001));
        count++;
        if((count=i%4)==0){
            printf(" ");
        }
    }
    printf("\n");
}

int ROL(uint32_t k, int n){
    k=(k<<n)|(k>>(32-n));
    printf("\n[ROR%d] ",n);
    print_bits(k);
    printf("\t(MSB bits moved to LSB)\n");
    return k;
}
int ROR(uint32_t k, int n){ 
    k=(k>>n)|(k<<(32-n));
    printf("\n[ROR%d] ",n);
    print_bits(k);    
    printf("\t(Restored to original)\n");
    return k;
}
int init(uint32_t k){
    printf("\n\n[Init] ");
    print_bits(k);
    return k;
}

int main(){
    uint32_t k=0xF0000000;
    int n=4;
    printf("=== Day 6: Circular Shift (Rotate) ===");
    k=init(k);
    k=ROL(k,n);
    k=ROR(k,n);

    return 0;
}
```

### 실행 결과

```bash
=== Day 6: Circular Shift (Rotate) ===

[Init]  Hex: 0xF0000000
Bin: 1111 0000 0000 0000 0000 0000 0000 0000

[ROR4]  Hex: 0x0000000F
Bin: 0000 0000 0000 0000 0000 0000 0000 1111
(MSB bits moved to LSB)

[ROR4]  Hex: 0xF0000000
Bin: 1111 0000 0000 0000 0000 0000 0000 0000
(Restored to original)
[1] + Done                       "/usr/bin/gdb" --interpreter=mi --tty=${DbgTerm} 0<"/tmp/Microsoft-MIEngine-In-1ymlpick.u1m" 1>"/tmp/Microsoft-MIEngine-Out-y11oprtb.0ro”
```
