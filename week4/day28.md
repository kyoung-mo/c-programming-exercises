# [4주차: 알고리즘 및 시스템 모사 (Algorithms & System)]
## Day 28. 가변 인자 함수 구현 (my_printf)
- **입력:** 포맷 스트링 `"%d %s"`, 가변 인자
- **출력:** 포맷팅된 문자열 출력
```c
int main() {
    printf("=== Day 28: Custom printf Implementation ===\n\n");

    // Test 1: 정수와 문자열
    my_printf("MyPrint: %d %s\n", 10, "test");

    // Test 2: 16진수와 음수
    my_printf("Hex: 0x%x, Negative: %d\n", 255, -12345);

    // Test 3: 여러 인자 혼합
    my_printf("Result: %d + %d = %d\n", 10, 20, 30);

    return 0;
}
```

참고

**va_start**와 **va_end**는 C언어에서 매개변수의 개수가 고정되지 않은 **가변 인자 함수(Variadic Function)**를 구현할 때 사용하는 매크로입니다. `<stdarg.h>` 헤더 파일에 정의되어 있습니다.

가변 인자 함수(예: `printf`)는 스택 메모리에 인자들이 연속적으로 쌓이는 원리를 이용하며, `va_start`와 `va_end`는 이 스택을 안전하게 탐색하고 정리하는 역할을 합니다.

---

### 1. 주요 매크로의 역할

가변 인자 처리를 위해서는 보통 4가지 매크로가 세트로 사용됩니다.

1. **`va_list`**: 가변 인자들의 목록을 가리키는 포인터 타입입니다. (스택의 주소를 저장)
2. **`va_start(ap, last_arg)`**: `ap` 포인터를 첫 번째 가변 인자의 주소로 초기화합니다. `last_arg`는 가변 인자가 시작되기 직전의 고정 매개변수입니다.
    - **`last_arg` 가 이나라 첫번째 아냐?**
        
        `va_start`의 두 번째 인자는 첫 번째 가변 인자가 아니라, 가변 인자(`...`)가 시작되기 직전의 **'마지막 고정 인자(Last Fixed Argument)'**를 의미함.
        
        매우 헷갈리기 쉬운 부분임. 용어의 기준이 '전체 매개변수'가 아니라 **'이름이 명시된 고정 매개변수'**이기 때문임.
        
        ---
        
        ### 1. `last_arg`의 정확한 의미
        
        - 함수 선언부에서 `...` 기호 바로 앞에 위치한 일반 매개변수의 이름을 넣어야 함.
        - 이름이 `last_arg`인 이유는 전달된 **고정 인자들 중 가장 마지막**에 위치하기 때문임.
        
        ### 2. 왜 '마지막 고정 인자'를 넘겨주는가? (동작 원리)
        
        - 컴파일러와 런타임은 스택 메모리 상에서 가변 인자(`...`)가 정확히 어디서부터 시작되는지 스스로 알지 못함.
        - 마지막 고정 인자의 메모리 주소를 알면, 그 주소에 해당 데이터 타입의 크기를 더해 **첫 번째 가변 인자의 시작 주소**를 역산할 수 있음.
        - 즉, `가변 인자 시작 주소 = 마지막 고정 인자의 주소 + 마지막 고정 인자의 메모리 크기` 공식을 풀기 위한 **기준점(오프셋 계산용)**으로 사용됨.
        
        ### 3. 명확한 예시 비교
        
        - **고정 인자가 1개일 때 (`printf` 스타일):**
            
            ```c
            void my_printf(const char *format, ...) {
                va_list ap;
                // format이 첫 번째 인자이자, 동시에 '마지막 고정 인자'임
                va_start(ap, format); 
            }
            ```
            
        - **고정 인자가 2개 이상일 때:**
            
            ```c
            void my_log(int level, const char *tag, ...) {
                va_list ap;
                // '...' 바로 앞의 인자인 tag를 전달해야 함.
                // level을 넣으면 스택 계산이 꼬여서 쓰레기값을 읽게 됨.
                va_start(ap, tag); 
            }
            ```
            
        
        ---
        
3. **`va_arg(ap, type)`**: 현재 `ap`가 가리키는 곳에서 `type` 크기만큼 데이터를 읽어 반환하고, 포인터를 다음 인자 위치로 이동시킵니다.
4. **`va_end(ap)`**: 가변 인자 처리가 끝났음을 알리고, 포인터를 `NULL`로 초기화하는 등 뒷정리를 수행합니다.

---

### 2. 메모리 구조와 동작 원리

함수가 호출될 때 인자들은 메모리의 **스택(Stack)** 영역에 역순 또는 순서대로 쌓입니다. 고정 인자 이후에 오는 가변 인자들은 주소상 연속적으로 배치되므로, 고정 인자의 주소만 알면 포인터 연산을 통해 뒤따라오는 인자들을 찾아낼 수 있습니다.

---

### 3. 간단한 구현 예제 (합계 구하기)

```c
#include <stdio.h>
#include <stdarg.h>

// count: 고정 인자 (뒤에 올 가변 인자의 개수를 알려줌)
int sum_all(int count, ...) {
    va_list ap;         // 1. 목록 포인터 선언
    int total = 0;

    va_start(ap, count); // 2. 가변 인자 시작 위치 초기화

    for (int i = 0; i < count; i++) {
        // 3. 하나씩 꺼내고 포인터 이동 (int 타입으로 해석)
        total += va_arg(ap, int); 
    }

    va_end(ap);          // 4. 정리
    return total;
}

int main() {
    // 3개의 인자를 더함: 10 + 20 + 30
    printf("Sum: %d\n", sum_all(3, 10, 20, 30));
    return 0;
}
```

---

### 4. 주의사항

- **타입 불일치**: `va_arg`에서 지정한 타입과 실제 전달된 인자의 타입이 다르면 메모리를 잘못 읽어 엉뚱한 값이 출력되거나 프로그램이 종료될 수 있습니다.
- **고정 인자 필수**: 가변 인자 함수는 최소 하나 이상의 고정 인자가 있어야 합니다. (어디서부터 가변 인자인지 시작점을 알아야 하기 때문입니다.)
- **종료 조건**: 가변 인자는 몇 개가 들어왔는지 스스로 알 수 없습니다. 위 예제처럼 개수를 넘겨주거나, 마지막에 특정 값(예: `NULL`)을 넣어 종료를 알려야 합니다.
    
<img width="1024" height="559" alt="image" src="https://github.com/user-attachments/assets/de768e6f-0183-4771-88f3-e38445ad266d" />

<img width="1024" height="559" alt="image" src="https://github.com/user-attachments/assets/0601e2be-7fd1-4834-9484-427a50843679" />


- **실행결과:**
```c
=== Day 28: Custom printf Implementation ===

MyPrint: 10 test
Hex: 0xFF, Negative: -12345
Result: 10 + 20 = 30
```

  
---


### 코드

```c
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>
/*
Day 28. 가변 인자 함수 구현 (my_printf)
- **입력:** 포맷 스트링 `"%d %s"`, 가변 인자
- **출력:** 포맷팅된 문자열 출력
- **제약조건:** `<stdarg.h>` 사용, `%d`, `%x`, `%s`만 지원.
*/
void my_printf(char* sentence, ...){
    va_list args;
    va_start(args, sentence);
    
    for(int i=0;i<strlen(sentence)+1;i++){
        
        if(sentence[i]!='%'){
        printf("%c",sentence[i]);
        }
        if(sentence[i]==0);
        else if(sentence[i]=='%'){
            i++;

            switch(sentence[i]){
                case 'd' : 
                printf("%d ",(int)va_arg(args, int));
                break;

                case 'x' :
                printf("%x ",(int)va_arg(args,unsigned int));

                case 's' :
                //printf("%s ", va_arg(args, char*));

                defaut : 
                printf("");
                break;
            }
        }
    }
    va_end(args);
}

int main(){

    printf("=== Day 28: Custom printf Implementation ===\n\n");

    // Test 1: 정수와 문자열
    my_printf("MyPrint: %d %s\n", 10, "test");
    // Test 2: 16진수와 음수
    my_printf("Hex: 0x%x, Negative: %d\n", 255, -12345);
    // Test 3: 여러 인자 혼합
    my_printf("Result: %d + %d = %d\n", 10, 20, 30);


    return 0;
}

// %s ?
```

### 실행 결과

```bash
=== Day 28: Custom printf Implementation ===

MyPrint: 10
Hex: 0xff , Negative: -12345
Result: 10  + 20  = 30
[1] + Done                       "/usr/bin/gdb" --interpreter=mi --tty=${DbgTerm} 0<"/tmp/Microsoft-MIEngine-In-0fgwh5d5.2ab" 1>"/tmp/Microsoft-MIEngine-Out-w1k3rfqh.4u2”
```
