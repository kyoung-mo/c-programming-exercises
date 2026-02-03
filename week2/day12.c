#include <stdio.h>
#include <stdint.h>
#define offsetof(TYPE, MEMBER) __builtin_offsetof (TYPE, MEMBER)
#define MY_MACRO(TYPE, MEMBER) \
    do { \
        int type=TYPE; \
        int mem = &MEMBER; \
        printf("[Standard] Offset of MEMBER: %d\n",mem-type); \
    } while(0)
/*
- **입력:** 구조체 타입명, 멤버 변수명
- **출력:** 구조체 시작 주소로부터 해당 멤버까지의 바이트 거리
- **제약조건:** `<stddef.h>` 표준 offsetof 사용 (비교용)  ⇒ 사용 금지. 0번지 주소 캐스팅 기법 활용.
*/

// 테스트를 위한 구조체 (패딩이 발생하는 구조)
typedef struct {
    char a;      
    int b;       
    double c;    
} Sample;


int main(){

    printf("=== Day 12: offsetof Implementation ===\n\n");
    uint32_t test;
    Sample* sample;
    MY_MACRO(sample,sample->a);
    MY_MACRO(sample,sample->b);
    MY_MACRO(sample,sample->c);

    printf("\n-----------------------------\n\n");

    test=offsetof(Sample, a);
    printf("[My Macro] Offset of a: %d\n",test);

    test=offsetof(Sample, b);
    printf("[My Macro] Offset of b: %d\n",test);

    test=offsetof(Sample, c);
    printf("[My Macro] Offset of c: %d\n",test);

    return 0;
}