# [2주차: 포인터와 메모리 관리 (Memory & Pointers)]
- **입력:** 임의의 메모리 주소, 길이
    
    ```c
    // 테스트 1: 단순 문자열 
        char my_text[] = "Hello Embedded World! This is Hexdump.";
        hexdump("String Dump", my_text, sizeof(my_text));
      
        // 테스트 2: 구조체 (엔디안 확인 가능)
        SensorData sensor = { 0x12345678, "Sensor A", 3.14f };
        hexdump("Struct Dump", &sensor, sizeof(sensor));
    ```
    
- **출력:** 주소 오프셋 | 16진수 데이터 16개 | ASCII 표현
- **제약조건:** 출력 불가능 문자는 `.`으로 표시.
- **실행결과:**

```c
String Dump:
  0000  48 65 6c 6c 6f 20 45 6d 62 65 64 64 65 64 20 57  Hello Embedded W
  0010  6f 72 6c 64 21 20 54 68 69 73 20 69 73 20 48 65  orld! This is He
  0020  78 64 75 6d 70 2e 00                             xdump..

Struct Dump:
  0000  78 56 34 12 53 65 6e 73 6f 72 20 41 00 00 00 00  xV4.Sensor A....
  0010  c3 f5 48 40                                      ..H@

```
---


### 코드

```c
#include <stdio.h>
#include <stdint.h>
#define MAX 100

typedef struct 
{
    uint32_t addr;
    char text[MAX];
    int size;

}SensorData;

void hexdump();
    
int main(){

    // 테스트 1: 단순 문자열 
    char my_text[] = "Hello Embedded World! This is Hexdump.";
    hexdump("String Dump", my_text, sizeof(my_text));
  
    // 테스트 2: 구조체 (엔디안 확인 가능)
    SensorData sensor = { 0x12345678, "Sensor A", 3.14f };
    hexdump("Struct Dump", &sensor, sizeof(sensor));


    return 0;
}

void hexdump(char str[12], unsigned char* addr, int size){
    printf("%s:\n",str);

    uint16_t line=0x0000;
    int count=0;
    for(int cnt=0;cnt<size;cnt+=16)
    {
        printf("  %04x  ",line);

        int bytes_left = size - count;
        int print_count = bytes_left < 16 ? bytes_left : 16;
        
        for(int i=0;i<print_count;i++)
        {
            printf("%02x ",addr[i+count]);
        }
        
        printf(" ");
        
        for(int i=0;i<print_count;i++){
            unsigned char c = addr[i+count];
            if(c >= 0x20 && c <= 0x7E)
                printf("%c", c);
            else
                printf(".");
        }
        printf("\n");
        line+=0x0010;
        count+=16;
    }

}
```

### 실행 결과

```bash
String Dump:
0000  48 65 6c 6c 6f 20 45 6d 62 65 64 64 65 64 20 57  Hello Embedded W
0010  6f 72 6c 64 21 20 54 68 69 73 20 69 73 20 48 65  orld! This is He
0020  78 64 75 6d 70 2e 00  xdump..
Struct Dump:
0000  78 56 34 12 53 65 6e 73 6f 72 20 41 00 00 00 00  xV4.Sensor A....
0010  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
0020  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
0030  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
0040  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
0050  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
0060  00 00 00 00 00 00 00 00 03 00 00 00  ............
[1] + Done                       "/usr/bin/gdb" --interpreter=mi --tty=${DbgTerm} 0<"/tmp/Microsoft-MIEngine-In-qefhntcc.rje" 1>"/tmp/Microsoft-MIEngine-Out-eil01fxo.qyv”
```
