#include <stdio.h>
#include <stdint.h>

// 전체적으로 수정 중
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
