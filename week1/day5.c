# [1주차: 비트 연산과 데이터 표현 (Bitwise & Data)]
## Day 5. 1의 개수 세기 (Population Count)
- **입력:** 32비트 정수
- **출력:** 켜져 있는 비트(1)의 개수
- **제약조건:** 루프(`for/while`) 없이 비트 연산만으로 구현 (Brian Kernighan 알고리즘 등 활용).
- **실행결과:**

```c
=== Day 5: Population Count (Counting Set Bits) ===

Case 1: Input 0x00000000
  [Naive]     : 0
  [Kernighan] : 0 (Recommended Logic)
  [SWAR]      : 0 (Strict Loop-free)
  [Built-in]  : 0
------------------------------
Case 2: Input 0x00000007
  [Naive]     : 3
  [Kernighan] : 3 (Recommended Logic)
  [SWAR]      : 3 (Strict Loop-free)
  [Built-in]  : 3
------------------------------
Case 3: Input 0x12345678
  [Naive]     : 13
  [Kernighan] : 13 (Recommended Logic)
  [SWAR]      : 13 (Strict Loop-free)
  [Built-in]  : 13
------------------------------
Case 4: Input 0xFFFFFFFF
  [Naive]     : 32
  [Kernighan] : 32 (Recommended Logic)
  [SWAR]      : 32 (Strict Loop-free)
  [Built-in]  : 32
------------------------------
```

---


### 코드

```c
#include <stdio.h>
#include <stdint.h>

// 루프 제한(while, for문 사용 금지)는 SWAR 에서만 구현
// 나머지는 비교용..? 인듯 하니  제약조건 상관 안쓰고 구현

void Naive(uint32_t n){
	int count =0;
	if(n&1==1) count++;
	while(n){
		if(((n>>=1)&1)==1){
			count++;
		}
	}
	printf("  [Naive]\t: %d\n",count);
}

void Kernighan(uint32_t n){
	int count =0;
	while(n){
		n=n&(n-1);
		count++;
	}
	printf("  [Kernighan]\t: %d (Recommended Logic)\n",count);
}

void SWAR(uint32_t n){
	uint32_t popCount;

    n=((n&0xAAAAAAAA) >> 1) + (n&0x55555555); // 1010 ... 1010 & n 이후 >> 1 + 0101 ... 0101 => 홀수 요소와 짝수 요소의 합
    n=((n&0xCCCCCCCC) >> 2) + (n&0x33333333); // 1100 ... 1100 & n 이후 >> 2 + n 값 => 4비트 내에서 2비트 + 2비트 결과 얻음 
    n=((n&0xF0F0F0F0) >> 4) + (n&0x0F0F0F0F); // 8비트에서 4비트 + 4비트 합
    n=((n&0xFF00FF00) >> 8) + (n&0x00FF00FF); // 16비트에서 8비트 + 8비트 합
    popCount=((n&0xFFFF0000) >> 16) + (n&0x0000FFFF); // 16비트에서 8비트 + 8비트 합

	printf("  [SWAR]\t: %d (Strict Loop-free)\n",popCount);
}

void Built_in(uint32_t n){
	printf("  [Built-in]\t: %d\n",__builtin_popcount(n));
}

void Print_bit(uint32_t n){
	Naive(n);
	Kernighan(n);
	SWAR(n);
	Built_in(n);
	printf("------------------------------\n");
}
int main(){
	uint32_t count_bit;

	printf("=== Day 5: Population Count (Counting Set Bits) ===\n");
	Print_bit(0x00000000);
	Print_bit(0x00000007);
	Print_bit(0x12345678);
	Print_bit(0xFFFFFFFF);
	
	return 0;

}

```

### 실행 결과

```bash

=== Day 5: Population Count (Counting Set Bits) ===
[Naive]       : 0
[Kernighan]   : 0 (Recommended Logic)
[SWAR]        : 0 (Strict Loop-free)
[Built-in]    : 0
------------------------------
[Naive]       : 3
[Kernighan]   : 3 (Recommended Logic)
[SWAR]        : 3 (Strict Loop-free)
[Built-in]    : 3
------------------------------
[Naive]       : 13
[Kernighan]   : 13 (Recommended Logic)
[SWAR]        : 13 (Strict Loop-free)
[Built-in]    : 13
------------------------------
[Naive]       : 32
[Kernighan]   : 32 (Recommended Logic)
[SWAR]        : 32 (Strict Loop-free)
[Built-in]    : 32
----------------------------—
```
