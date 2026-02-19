# [4주차: 알고리즘 및 시스템 모사 (Algorithms & System)]
## Day 23. 문자열 토크나이저 (strtok 재구현)
- **입력:** "GPS,37.5665,126.9780,20260213", 구분자 ','
- **출력:** 순차적으로 파싱된 문자열
- **제약조건:** 내부 정적 변수(`static`)를 사용하여 상태 저장, 원본 문자열 수정 없이 구현해볼 것(선택).
- **실행결과:**

```c
=== Day 23: Safe String Tokenizer (static) ===

Input Data: "GPS,37.5665,126.9780,20260213"
Delimiter : ','

Token 1: GPS
Token 2: 37.5665
Token 3: 126.9780
Token 4: 20260213

>> Original string check: "GPS,37.5665,126.9780,20260213"
>> (Original string remains unmodified)
```

---


### 코드

```c
#include <stdio.h>
#include <string.h>
/*
Day 23. 문자열 토크나이저 (strtok 재구현)
- **입력:** "GPS,37.5665,126.9780,20260213", 구분자 ','
- **출력:** 순차적으로 파싱된 문자열
- **제약조건:** 내부 정적 변수(`static`)를 사용하여 상태 저장, 원본 문자열 수정 없이 구현해볼 것(선택).
*/

char* my_strtok(char* str, char delimiters){
    static char* pos = NULL;
    static char buffer[256];

    if(str != NULL)
        pos = str;

    if(pos == NULL || *pos == '\0')
        return NULL;

    int k=0;
    while(*pos != '\0' && *pos != delimiters){
        buffer[k] = *pos;
        k++;
        pos++;
    }
    buffer[k] = '\0';

    if(*pos == delimiters)
        pos++;

    return buffer;
}

void prt_str(char* str, char delimiters){
    printf("Input Data: \"%s\"\n",str);
    printf("Delimiter : '%c'\n\n",delimiters);

    int cnt=1;
    char* token = my_strtok(str, delimiters);
    while(token != NULL){
        printf("Token %d: %s\n",cnt,token);
        cnt++;
        token = my_strtok(NULL, delimiters);
    }
}

int main(){

    printf("=== Day 23: Safe String Tokenizer (static) ===\n\n");

    static char* str={"GPS,37.5665,126.9780,20260213"};
    static char delimiters={','};

    prt_str(str, delimiters);

    printf("\n>> Original string check: \"%s\"\n",str);
    printf(">> (Original string remains unmodified)");

    return 0;
}
```

### 실행 결과

```bash
=== Day 23: Safe String Tokenizer (static) ===

Input Data: "GPS,37.5665,126.9780,20260213"
Delimiter : ','

Token 1: GPS
Token 2: 37.5665
Token 3: 126.9780
Token 4: 20260213

>> Original string check: "GPS,37.5665,126.9780,20260213"
>> (Original string remains unmodified)[1] + Done                       "/usr/bin/gdb" --interpreter=mi --tty=${DbgTerm} 0<"/tmp/Microsoft-MIEngine-In-claqtm4q.v4w" 1>"/tmp/Microsoft-MIEngine-Out-dkogrbzp.dn3”
```
