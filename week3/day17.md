# [3주차: 임베디드 필수 자료구조 (Data Structures)]
## Day 17. 비트맵 (Bitmap) 관리자
- **입력:** 관리할 리소스 개수(예: 100개), 할당/해제 요청
- **출력:** 할당된 인덱스 번호
- **제약조건:** `uint8_t` 배열을 비트 단위로 쪼개서 사용 여부 마킹 (1bit = 1resource).
- **실행결과:**  ⇒ 화면에는 3개정도만 보여준다. 

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
[Bitmap Visual] 11111111 | 00000000 | 00000000

Freeing index 2...
>> Index 2 freed. (Byte 0, Bit 2 cleared)
[Bitmap Visual] 11011111 | 00000000 | 00000000

Allocating again (expecting index 2)...
>> Index 2 allocated. (Byte 0, Bit 2 set)
[Bitmap Visual] 11111111 | 00000000 | 00000000
```
<img width="1200" height="600" alt="image" src="https://github.com/user-attachments/assets/57ea8088-a3e4-42af-972d-79250803e3dc" />

---


### 코드

```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#define MAX_RESOURCES 32

uint8_t bitmap[MAX_RESOURCES / 8];  
int total_resources = 24;     

void print_bitmap();
int allocate_resource();
void free_resource(int index);

int main() {
    printf("=== Day 17: Bitmap Manager === \n\n");
    
    for (int i = 0; i < MAX_RESOURCES / 8; i++) {
        bitmap[i] = 0;
    }
    
    for (int i = 0; i < 8; i++) {
        allocate_resource();
    }
    print_bitmap();
    printf("\n");
    
    printf("Freeing index 2...\n");
    free_resource(2);
    print_bitmap();
    printf("\n");
    
    printf("Allocating again (expecting index 2)...\n");
    allocate_resource();
    print_bitmap();
    
    return 0;
}

void print_bitmap() {
    printf("[Bitmap Visual] ");
    for (int byte_idx = 0; byte_idx < 3; byte_idx++) { 
        for (int bit_idx = 7; bit_idx >= 0; bit_idx--) {
            printf("%d", (bitmap[byte_idx] >> bit_idx) & 1);
        }
        if (byte_idx < 2) printf(" | ");
    }
    printf("\n");
}

int allocate_resource() {
    for (int idx = 0; idx < total_resources; idx++) {
        int byte_idx = idx / 8;
        int bit_idx = idx % 8;
        
        if ((bitmap[byte_idx] & (1 << bit_idx)) == 0) {
            bitmap[byte_idx] |= (1 << bit_idx);  
            printf(">> Index %d allocated. (Byte %d, Bit %d set)\n", 
                   idx, byte_idx, bit_idx);
            return idx;
        }
    }
    printf(">> No available resource!\n");
    return -1;
}

void free_resource(int index) {
    if (index < 0 || index >= total_resources) {
        printf(">> Invalid index!\n");
        return;
    }
    
    int byte_idx = index / 8;
    int bit_idx = index % 8;
    
    bitmap[byte_idx] &= ~(1 << bit_idx);  
    printf(">> Index %d freed. (Byte %d, Bit %d cleared)\n", 
           index, byte_idx, bit_idx);
}
```

### 실행 결과

```bash
=== Day 17: Bitmap Manager ===

>> Index 0 allocated. (Byte 0, Bit 0 set)
>> Index 1 allocated. (Byte 0, Bit 1 set)
>> Index 2 allocated. (Byte 0, Bit 2 set)
>> Index 3 allocated. (Byte 0, Bit 3 set)
>> Index 4 allocated. (Byte 0, Bit 4 set)
>> Index 5 allocated. (Byte 0, Bit 5 set)
>> Index 6 allocated. (Byte 0, Bit 6 set)
>> Index 7 allocated. (Byte 0, Bit 7 set)
[Bitmap Visual] 11111111 | 00000000 | 00000000

Freeing index 2...
>> Index 2 freed. (Byte 0, Bit 2 cleared)
[Bitmap Visual] 11111011 | 00000000 | 00000000

Allocating again (expecting index 2)...
>> Index 2 allocated. (Byte 0, Bit 2 set)
[Bitmap Visual] 11111111 | 00000000 | 00000000
[1] + Done                       "/usr/bin/gdb" --interpreter=mi --tty=${DbgTerm} 0<"/tmp/Microsoft-MIEngine-In-hn4r3eop.lzs" 1>"/tmp/Microsoft-MIEngine-Out-in5bzt2z.c5f”
```
