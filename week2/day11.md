# [2주차: 포인터와 메모리 관리 (Memory & Pointers)]
## Day 11. 함수 포인터 배열을 이용한 계산기
- **입력:** 연산자 ID (0:Add, 1:Sub, 2:Mul...), 두 정수
- **출력:** 연산 결과
- **제약조건:** `if`나 `switch` 문 사용 금지. enum사용
- **실행결과:**

```bash
=== Day 11: Function Pointer Array Calculator ===

Select (0:Add, 1:Sub, 2:Mul, 3:Div, 4:Exit): 0
Input two integers: 1 2
>> Result: 3

Select (0:Add, 1:Sub, 2:Mul, 3:Div, 4:Exit): 1
Input two integers: 2 1
>> Result: 1

Select (0:Add, 1:Sub, 2:Mul, 3:Div, 4:Exit): 2
Input two integers: 2 1
>> Result: 2

Select (0:Add, 1:Sub, 2:Mul, 3:Div, 4:Exit): 3
Input two integers: 1 2
>> Result: 0

Select (0:Add, 1:Sub, 2:Mul, 3:Div, 4:Exit): 4

```
---


### 코드

```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

enum op_id
{
    Add,
    Sub,
    Mul,
    Div,
    Exit
};

int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
int mul(int a, int b) { return a * b; }
int div(int a, int b) { return a / b; }
int exit(int a, int b) { return 0; }

int main()
{
    int res;
    int sel=0;
    int (*fp[4])(int, int);
    printf("=== Day 11: Function Pointer Array Calculator ===\n\n");

    while (sel<=3 && sel>=0)
    {
        int a, b, res;
        int (*fp[4])(int, int) = {add, sub, mul, div, exit};
        printf("Select (0:Add, 1:Sub, 2:Mul, 3:Div, 4:Exit): ");
        scanf("%d", &sel);

        printf("Input two integers: ");
        scanf("%d %d", &a, &b);

        res = fp[sel](a, b);

        printf(">> Result: %d\n\n",res);
    }

    return 0;
}
```

### 실행 결과

```bash
=== Day 11: Function Pointer Array Calculator ===

Select (0:Add, 1:Sub, 2:Mul, 3:Div, 4:Exit): 0
Input two integers: 1 2
>> Result: 3

Select (0:Add, 1:Sub, 2:Mul, 3:Div, 4:Exit): 1
Input two integers: 2 1
>> Result: 1

Select (0:Add, 1:Sub, 2:Mul, 3:Div, 4:Exit): 2
Input two integers: 2 1
>> Result: 2

Select (0:Add, 1:Sub, 2:Mul, 3:Div, 4:Exit): 3
Input two integers: 1 2
>> Result: 0

Select (0:Add, 1:Sub, 2:Mul, 3:Div, 4:Exit): 4
Input two integers: 2 4
[1] + Done                       "/usr/bin/gdb" --interpreter=mi --tty=${DbgTerm} 0<"/tmp/Microsoft-MIEngine-In-4yy3klo1.wgk" 1>"/tmp/Microsoft-MIEngine-Out-llzctkre.1z4”
```
