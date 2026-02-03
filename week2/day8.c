#include <stdio.h>
#include <stdint.h>
#include <string.h>

/*
- **입력:** 소스 주소, 목적지 주소, 복사할 바이트 수
- **출력:** 메모리 복사 후 목적지 주소의 데이터 덤프
- **제약조건:** `memcpy` 대신 `memmove` 동작 구현 (src와 dest 영역이 겹칠 때 데이터 오염 방지).
- **실행결과:** `Overlap handled correctly.`
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

uint32_t * memory_move(void * dest, const void *src, size_t n){
    char *d = (char*)dest;
    char *s = (char*)src;
    
    if(d > s && d < s + n){
        uint32_t* buffer = src;
        return buffer;
    }
    else return memcpy(dest, src, n);
}

int main(){

    uint32_t initial_memory = 69999;
    uint32_t *src=&initial_memory;
    uint32_t *dest=(uint32_t*)((char*)src+2);
    uint32_t n=sizeof(*src);



    printf("src 바이트: 0x%08X\n", *src);
    printf("dest 바이트: 0x%08X\n", *dest);
    printf("*src : ");    
    PRT_BIT(*src);

    dest=memory_move(dest,src,4);    
    
    printf("src 바이트: %08x\n", *src);
    printf("dest 바이트: 0x%08X\n", *dest);
    printf("*dest : ");
    PRT_BIT(*dest); 

    return 0;
}