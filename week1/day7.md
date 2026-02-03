# [1주차: 비트 연산과 데이터 표현 (Bitwise & Data)]
## Day 7. Checksum 계산 (XOR 방식) LCR <⇒ CRC
- **입력:** 바이트 배열  payload`[`0x10, 0x20, 0x30, 0x40`]`, 길이, ID
- **출력:** XOR 누적 체크섬 값
- **제약조건:** 포인터 연산 사용.
- **실행결과:**

```c
=== Day 7: XOR Checksum Calculation ===

[TX] Sending Packet...
     Data: 0x01 0x04 0x10 0x20 0x30 0x40 
     Calculated Checksum: 0x04

[RX] Receiving Normal Packet...
     >> Verification SUCCESS (Result: 0x00)

[RX] Receiving Corrupted Packet (Noise injected)...
     Corrupted Data: 0x01 0x04 0xEF 0x20 0x30 0x40 0x04 
     >> Verification FAIL (Result: 0xFF)
     >> Error detected! Discarding packet.
```

---


### 코드

```c
#include <stdio.h>
#include <stdint.h>
#include <string.h>

/*
- **입력:** 바이트 배열 `[0x01, 0x02, 0x03, 0x04]`, 길이
- **출력:** XOR 누적 체크섬 값
- **제약조건:** 포인터 연산 사용.
*/

// 패킷 구조체 (데이터 + 체크섬)
typedef struct {
    uint8_t id;
    uint8_t length;
    uint8_t payload[4];
    uint8_t checksum;
} Packet;

/*
 * [XOR Checksum 계산 함수]
 * data: 데이터 시작 주소
 * len: 데이터 길이
 * 반환값: 계산된 체크섬 바이트
 * 제약조건: 포인터 연산 사용 (*ptr++)
 */

uint8_t calc_checksum(const uint8_t *data, size_t len) { // XOR 연산 체크썸
    uint8_t checksum = 0;
    for(int i=0;i<len;i++){
        checksum^=data[i];
    }
    return checksum;
}

void sending_data(uint8_t data[]){  // 문제 x
    printf("[TX] Sending Packet...\n");
    printf("\tData: 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X\n",data[0],data[1],data[2],data[3],data[4],data[5]);
}

void receiving_data(uint8_t data[], uint8_t checksum, size_t len){ // ?
    uint8_t result=0;
    for(int i=0;i<len;i++){
        result^=data[i+2];
    }
    result^=checksum;
    
    if(result==0){
        printf("[RX] Receiving Normal Packet...\n");
        printf("\t>> Verification SUCCESS (Result: 0x%02X)\n\n",result);
    }
    else{
        printf("[RX] Receiving Corrupted Packet (Noise injected)...\n");
        printf("\tCorrupted Data: 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X\n",data[0],data[1],data[2],data[3],data[4],data[5]);
        printf("\t>> Verification FAIL (Result: 0x%02X)\n",result);
        printf("\t>> Error detected! Discarding packet.\n");
    }
}

int main() {

    Packet packet;
    printf("=== Day 7: XOR Checksum Calculation ===\n\n");

    // 1. 송신 데이터 준비 (헤더 + 데이터)
    // ID: 0x01, LEN: 4, DATA: {0x10, 0x20, 0x30, 0x40}
    uint8_t raw_data[] = { 0x01, 0x04, 0x10, 0x20, 0x30, 0x40 };

    packet.id=raw_data[0];
    packet.length=raw_data[1];
    packet.payload[0]=raw_data[2];
    packet.payload[1]=raw_data[3];
    packet.payload[2]=raw_data[4];
    packet.payload[3]=raw_data[5];
    packet.checksum=calc_checksum(packet.payload, packet.length);

    sending_data(&packet);
    printf("\tCalculated Checksum: 0x%02X\n\n", packet.checksum);
    receiving_data(&packet,packet.checksum,packet.length);

    // 4. 수신 시뮬레이션 (에러 발생 케이스)
    packet.payload[2]^=0xFF;    // 3번째 바이트(0x10)에 비트 반전 노이즈 발생!    
    receiving_data(&packet,packet.checksum,packet.length);

    
    
    return 0;
}
```

### 실행 결과

```bash
=== Day 7: XOR Checksum Calculation ===

[TX] Sending Packet...
Data: 0x01 0x04 0x10 0x20 0x30 0x40
Calculated Checksum: 0x40

[RX] Receiving Normal Packet...
>> Verification SUCCESS (Result: 0x00)

[RX] Receiving Corrupted Packet (Noise injected)...
Corrupted Data: 0x01 0x04 0x10 0x20 0xCF 0x40
>> Verification FAIL (Result: 0xFF)
>> Error detected! Discarding packet.
[1] + Done                       "/usr/bin/gdb" --interpreter=mi --tty=${DbgTerm} 0<"/tmp/Microsoft-MIEngine-In-f25pmq5w.rge" 1>"/tmp/Microsoft-MIEngine-Out-z3wfdgoy.x2a”
```
