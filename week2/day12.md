# [2주차: 포인터와 메모리 관리 (Memory & Pointers)]
## Day 12. 구조체 멤버 오프셋 매크로 (offsetof 구현)
이 문제는 **"구조체 내부에서 특정 멤버가 시작점으로부터 몇 바이트 떨어져 있는지"**를 구하는 매크로를 직접 구현하는 것입니다.

이것은 리눅스 커널이나 임베디드 드라이버 개발에서 **하드웨어 레지스터 맵핑**이나 **`container_of` 매크로**를 이해하기 위한 가장 중요한 기초 지식입니다.

- **입력:** 구조체 타입명, 멤버 변수명
- **출력:** 구조체 시작 주소로부터 해당 멤버까지의 바이트 거리
- **제약조건:** `<stddef.h>` 표준 offsetof 사용 (비교용)  ⇒ 사용 금지. 0번지 주소 캐스팅 기법 활용.
- **실행결과:**

```bash
=== Day 12: offsetof Implementation ===

Struct Size: 16 bytes

[Standard] Offset of a: 0
[Standard] Offset of b: 4
[Standard] Offset of c: 8

-----------------------------

[My Macro] Offset of a: 0
[My Macro] Offset of b: 4
[My Macro] Offset of c: 8

>> Success! Implementation is correct.
```

### 참고

```bash
#include <stddef.h> // size_t, 원래 offsetof가 들어있는 헤더

// 테스트를 위한 구조체 (패딩이 발생하는 구조)
typedef struct {
    char a;      // 1 byte
    // (padding 3 bytes) - 4바이트 정렬을 위해 컴파일러가 넣음
    int b;       // 4 bytes
    double c;    // 8 bytes
} Sample;
```
---


### 코드

```c
#include <stdio.h>
#define offsetof(TYPE, MEMBER) __builtin_offsetof (TYPE, MEMBER)
#define MY_MACRO(TYPE, MEMBER) \
    do { \
        printf("type=%d\n",TYPE); \
        printf("MEMBER=%d\n",(TYPE+sizeof(MEMBER))); \
        printf("[Standard] Offset of a: %d\n",sizeof(MEMBER)); \
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
    int test;
    Sample* sample;
    MY_MACRO(sample,sample->a);
    MY_MACRO(sample,sample->b);
    MY_MACRO(sample,sample->c);

    printf("\n-----------------------------\n\n");

    test=offsetof(Sample, a);
    printf("test = %d\n",test);

    test=offsetof(Sample, b);
    printf("test = %d\n",test);

    test=offsetof(Sample, c);
    printf("test = %d\n",test);

    return 0;
}
```

### 이후 수정 코드 
```c
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
```

### 실행 결과

```bash
=== Day 12: offsetof Implementation ===

type=-9184
MEMBER=-9056
[Standard] Offset of a: 8
type=-9184
MEMBER=-9056
[Standard] Offset of a: 8
type=-9184
MEMBER=-9056
[Standard] Offset of a: 8

-----------------------------

test = 0
test = 4
test = 8
[1] + Done                       "/usr/bin/gdb" --interpreter=mi --tty=${DbgTerm} 0<"/tmp/Microsoft-MIEngine-In-xhhwrjsk.rrl" 1>"/tmp/Microsoft-MIEngine-Out-quazsvye.i3l”

============ 수정 결과 ================


=== Day 12: offsetof Implementation ===

[Standard] Offset of MEMBER: 0
[Standard] Offset of MEMBER: 4
[Standard] Offset of MEMBER: 8

-----------------------------

[My Macro] Offset of a: 0
[My Macro] Offset of b: 4
[My Macro] Offset of c: 8
[1] + Done                       "/usr/bin/gdb" --interpreter=mi --tty=${DbgTerm} 0<"/tmp/Microsoft-MIEngine-In-g3mlaoep.mim" 1>"/tmp/Microsoft-MIEngine-Out-42s3m2du.d10”
```
<img width="791" height="233" alt="image" src="https://github.com/user-attachments/assets/af71caf0-7254-47a1-bcbd-6f0b7b6097b2" />
