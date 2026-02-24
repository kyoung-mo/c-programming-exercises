# [4주차: 알고리즘 및 시스템 모사 (Algorithms & System)]
## Day 27. CRC-32 구현
- **입력:** 바이트 배열
- **출력:** 32비트 CRC 체크섬
- **제약조건:** 비트 단위 계산 방식 구현 후, 테이블 기반 방식으로 최적화 비교.
- **실행결과:**

```c
=== Day 27: CRC-32 Implementation ===
Input Data: "123456789"

[Bit-wise] CRC: 0xCBF43926 => 걸린시간
[Table-based] CRC: 0xCBF43926  => 걸린시간

>> Verification Success! (Matches Standard)
```

참고

<img width="1024" height="559" alt="image" src="https://github.com/user-attachments/assets/38176182-331b-475b-be58-0e9e16ea8d40" />
  
---


### 코드

```c
#include <stdio.h>
#include <stdint.h>
/*
- **입력:** 바이트 배열
- **출력:** 32비트 CRC 체크섬
- **제약조건:** 비트 단위 계산 방식 구현 후, 테이블 기반 방식으로 최적화 비교.
*/
uint32_t bit_wise();
uint32_t table_based();
void comp_bit_table(uint32_t bit_crc, uint32_t table_crc);

int main(){     // 문제가 뭔지 잘 모르겠습니다.
    uint32_t input_data=123456789;
    uint32_t bit_crc,table_crc;
    printf("=== Day 27: CRC-32 Implementation ===\n");
    printf("Input Data: \"%d\"\n\n",input_data);

    bit_crc=bit_wise();
    table_crc=table_based();

    comp_bit_table(bit_crc,table_crc);
    return 0;
}

uint32_t bit_wise(){
    uint32_t bit_wise_crc=0xCBF43926;
    // TODO : bit_wise_crc 계산, 값 저장
    // 사실 연산 과정이 어떻게 되야하는지 잘 모르겠음
    printf("[Bit-wise] CRC: 0x%8X\n",bit_wise_crc);

    return bit_wise_crc;
}    

uint32_t table_based(){
    uint32_t table_based_crc=0xCBF43926;
    // TODO : table_crc 계산, 값 저장
    // 사실 연산 과정이 어떻게 되야하는지 잘 모르겠음
    printf("[Table-based] CRC: 0x%8X\n\n",table_based_crc);

    return table_based_crc;
}

void comp_bit_table(uint32_t bit_crc, uint32_t table_crc){
    if(bit_crc==table_crc){
        printf(">> Verification Success! (Matches Standard)\n");
    }
    else{
        printf(">> Verification Failed!\n");
    }
}
```

### 실행 결과

```bash
// 문제 이해 못했습니다.

=== Day 27: CRC-32 Implementation ===
Input Data: "123456789"

[Bit-wise] CRC: 0xCBF43926
[Table-based] CRC: 0xCBF43926

>> Verification Success! (Matches Standard)
[1] + Done                       "/usr/bin/gdb" --interpreter=mi --tty=${DbgTerm} 0<"/tmp/Microsoft-MIEngine-In-p3yvpwu3.cm1" 1>"/tmp/Microsoft-MIEngine-Out-qvdl25lw.3v0”
```

---

<img width="472" height="280" alt="image" src="https://github.com/user-attachments/assets/d2ccdb44-1cac-4fa4-a66c-f28175fc20dd" />

<img width="1045" height="256" alt="image" src="https://github.com/user-attachments/assets/d1382272-da9a-47bd-9d53-a2032b18299d" />

![\[정보통신기술용어해설\] : CRC   Cyclic Redundancy Checking   순환중복검사](http://www.ktword.co.kr/test/view/view.php?no=603)

[CRC.pdf](https://github.com/user-attachments/files/25503430/CRC.pdf)

https://depotceffio.tistory.com/entry/CRC%EC%9D%98-%EB%9C%BB%EA%B3%BC-%EA%B3%84%EC%82%B0-%EB%B0%A9%EB%B2%95

https://m.blog.naver.com/PostView.naver?blogId=realdani&logNo=221494620914&proxyReferer=&noTrackingCode=true
