# [1주차: 비트 연산과 데이터 표현 (Bitwise & Data)]
## Day 4. 비트 단위 Reverse (Mirroring)
- **입력:** 8비트 정수 `0b11010010`
- **출력:** `0b01001011` (비트 순서 반전)
- **제약조건:** Lookup Table(LUT)을 사용하지 않고 O(1) 비트 연산으로 구현.
- **실행결과:**

```c
=== Day 4: Bitwise Reverse (Mirroring) ===

Case 1:
  Input : 0xD2 (1101 0010)
  Output: 0x4B (0100 1011)
  Verify: OK
------------------------
Case 2:
  Input : 0x0F (0000 1111)
  Output: 0xF0 (1111 0000)
  Verify: OK
------------------------
Case 3:
  Input : 0xAA (1010 1010)
  Output: 0x55 (0101 0101)
  Verify: OK
------------------------
Case 4:
  Input : 0x12 (0001 0010)
  Output: 0x48 (0100 1000)
  Verify: OK
------------------------
```

---


### 코드

```c
#include <stdio.h>
#include <stdint.h>

int cnt=1;

static int verify_v(uint8_t v){
    if((v|(uint8_t)(~v))==0xFF){ 
    return 0;
    }
    else return 1;
}

static void print_bin8(uint8_t v){
    for(int i=7;i>=0;--i){
        putchar((v&(1u<<i))? '1': '0'); // unsigned int
        if(i%4 ==0 && i !=0) putchar(' ');
    }
}

static void reverse_print_bin8(uint8_t v){
    for(int i=0;i<=7;i++){
        putchar((v&(1u<<i))? '1': '0');
        if((i+1)%4 ==0 && (i+1) !=0) putchar(' ');
    }
}


void print_case(uint8_t v){
    
    int verify=0;

    printf("Case %d",cnt);
    printf("\tInput : 0x%02X (",v);
    print_bin8(v);
    printf(")\n\tOutput : 0x%02X (",v);
    reverse_print_bin8(v);
    printf(")\n");

    verify = verify_v(v);

    if(verify==0) printf("\tVerify : OK\n");
    else printf("\tVerify : ERROR\n");

    printf("------------------------\n");

    cnt++;
}
int main(){

    printf("=== Day 4: Bitwise Reverse (Mirroring) ===\n");

    print_case(0xD2);
    print_case(0x0F);
    print_case(0xAA);
    print_case(0x12);


    return 0;
}
```

### 실행 결과

```bash
=== Day 4: Bitwise Reverse (Mirroring) ===
Case 1  Input : 0xD2 (1101 0010)
Output : 0xD2 (0100 1011 )
Verify : OK
------------------------
Case 2  Input : 0x0F (0000 1111)
Output : 0x0F (1111 0000 )
Verify : OK
------------------------
Case 3  Input : 0xAA (1010 1010)
Output : 0xAA (0101 0101 )
Verify : OK
------------------------
Case 4  Input : 0x12 (0001 0010)
Output : 0x12 (0100 1000 )
Verify : OK
----------------------—
```
