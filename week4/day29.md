# [4주차: 알고리즘 및 시스템 모사 (Algorithms & System)]
## Day 29. 간단한 협력형 스케줄러 (Cooperative Scheduler)
- **입력:** 태스크 3개 등록
- **출력:** 태스크가 순차적으로 실행되고 양보(`yield`)하는 로그
- **제약조건:** `setjmp`, `longjmp`를 사용하여 컨텍스트 스위칭 흉내 내기.
- 실행결과: 
```c
=== Day 29: Simple Cooperative Scheduler ===

[Task A] Start working... (Step 1)
  [Task B] Processing Data...
    [Task C] Initialization
[Task A] Resumed working... (Step 2)
  [Task B] Processing Data...
    [Task C] Calculation
[Task A] Start working... (Step 1)
  [Task B] Processing Data...
    [Task C] Finalize
[Task A] Resumed working... (Step 2)

>> Simulation Finished.
```


---


### 코드

```c
#include <stdio.h>
#include <setjmp.h>
/*
Day 29. 간단한 협력형 스케줄러 (Cooperative Scheduler)
- **입력:** 태스크 3개 등록
- **출력:** 태스크가 순차적으로 실행되고 양보(`yield`)하는 로그
- **제약조건:** `setjmp`, `longjmp`를 사용하여 컨텍스트 스위칭 흉내 내기.
*/

jmp_buf env;

void task_a(int ret){
    if(ret%2==0){
        printf("[Task A] Start working... (Step 1)\n");
    }
    else{
        printf("[Task A] Resumed working... (Step 2)\n");        
    }
    task_b(ret);
}

void task_b(int ret){
    if(ret<=2) printf("  [Task B] Processing Data...\n");
    task_c(ret);
}

void task_c(int ret){
    if(ret==0){
        printf("    [Task C] Initialization\n");
        longjmp(env,++ret);
    }
    else if(ret==1){
        printf("    [Task C] Calculation\n");
        longjmp(env,++ret);
    }
    else if(ret==2){
        printf("    [Task C] Finalize\n");
        longjmp(env,++ret);
    }
}

int main(){

    printf("=== Day 29: Simple Cooperative Scheduler ===\n\n");

    volatile int ret=setjmp(env);
    task_a(ret);
    if(ret>2){
        printf("\n>> Simulation Finished.\n");
        return -1;
    }
    else{
        task_a(ret);    
    }
    
    

    return 0;
}
```

### 실행 결과

```bash
=== Day 29: Simple Cooperative Scheduler ===

[Task A] Start working... (Step 1)
[Task B] Processing Data...
[Task C] Initialization
[Task A] Resumed working... (Step 2)
[Task B] Processing Data...
[Task C] Calculation
[Task A] Start working... (Step 1)
[Task B] Processing Data...
[Task C] Finalize
[Task A] Resumed working... (Step 2)

>> Simulation Finished.
[1] + Done                       "/usr/bin/gdb" --interpreter=mi --tty=${DbgTerm} 0<"/tmp/Microsoft-MIEngine-In-ajcymewv.mrw" 1>"/tmp/Microsoft-MIEngine-Out-quc3toox.5i4”
```

---

- 참고
    
    C언어의 `setjmp`와 `longjmp`는 함수 호출 스택(Call Stack)을 **무시하고** 과거의 특정 실행 지점으로 즉시 되돌아가는 '**비지역 분기(Non-local Goto)**' 기능을 제공함. 주로 깊숙한 함수 체인에서의 예외(Error) 처리나 협력형 스케줄러(Coroutine) 구현에 사용됨.
    
    ---
    
    ### 1. 핵심 동작 원리
    
    마치 게임의 **'세이브 포인트 생성'**과 **'세이브 데이터 불러오기'**와 같음.
    
    - **`jmp_buf`:** CPU의 레지스터 상태(Program Counter, Stack Pointer 등 컨텍스트)를 저장하는 특수 배열 타입.
    - **`setjmp(jmp_buf env)` [세이브]:**
        - 현재의 CPU 상태를 `env`에 저장함.
        - 코드가 **순차적으로 실행**되어 최초로 호출될 때는 **`0`을 반환**함.
    - **`longjmp(jmp_buf env, int val)` [로드]:**
        - `env`에 저장된 상태를 복원하여, 프로그램의 실행 흐름을 과거 `setjmp`가 호출되었던 위치로 강제 이동시킴.
        - 이때 `setjmp`는 마치 방금 호출된 것처럼 동작하지만, 최초 호출과 구분하기 위해 **`longjmp`가 전달한 `val` 값을 반환**함. (참고: `val`에 0을 넣어도 시스템이 강제로 1로 바꿔서 반환함)
    
    ### 2. 코드 예시 (예외 처리 모사)
    
    ```c
    #include <stdio.h>
    #include <setjmp.h>
    
    jmp_buf err_buf;
    
    void calculate(int a, int b) {
     
        if (b == 0) {
            // 에러 발생! 깊은 스택에서 즉시 main()의 setjmp 위치로 탈출
            longjmp(err_buf, 99); 
        }
        printf("Result: %d\n", a / b);
    }
    
    int main() {
        // 세이브 포인트 설정
        int status = setjmp(err_buf); 
    
        if (status == 0) {
            // 1. 최초 실행 흐름
            printf("Start calculation...\n");
            calculate(10, 0); // 내부에서 longjmp가 호출됨
            printf("This line is skipped.\n");
        } else {
            // 2. longjmp를 통해 점프해 온 흐름
            printf("Exception Caught! Error code: %d\n", status); // 99 출력됨
        }
    
        return 0;
    }
    ```
    
    <img width="1024" height="559" alt="image" src="https://github.com/user-attachments/assets/c35e031f-6c8c-4dc5-af3d-7c5993be5d0e" />

    
    ### 3. 실무 사용 시 치명적 주의사항 (Gotchas)
    
    로우 레벨 제어인 만큼 컴파일러 최적화 및 스택 구조와 충돌할 위험이 높음.
    
    - **메모리 누수 (Memory Leak):** C++의 `try-catch` 스택 언와인딩(Stack Unwinding) 메커니즘과 다름. 점프하는 구간 사이에 동적 할당된 메모리(`malloc`)가 있거나, 열린 파일(`fopen`)이 있어도 **자동으로 해제해주지 않음**.
    - **`volatile` 선언 필수:** `setjmp` 이후에 값이 변경된 지역 변수는 `longjmp`로 돌아왔을 때 이전 값으로 롤백될 위험이 있음(컴파일러가 레지스터에 값을 캐싱하기 때문). 상태를 유지해야 하는 지역 변수는 반드시 `volatile int flag;` 형태로 선언하여 메모리 접근을 강제해야 함.
    - **무효화된 스택으로의 점프 금지:** `setjmp`를 호출했던 함수가 이미 `return`하여 종료되었다면, 그 함수의 스택 프레임은 파괴된 것임. 이때 그곳으로 `longjmp`를 시도하면 미정의 동작(UB, 프로그램 크래시)이 발생함. 반드시 **현재 함수나 더 상위 호출자(Caller) 방향**으로만 점프해야 함.
    
    ---
    
- 참고2
    
    <img width="1024" height="559" alt="image" src="https://github.com/user-attachments/assets/7b4413db-7dc3-4852-9544-5dc4a025fbc2" />

    
- goto / longjmp
    
    가장 큰 차이는 **점프 가능한 범위(Scope)**와 **컨텍스트(Context) 보존 여부**임. `goto`는 단일 함수 내에서만 이동하는 **지역(Local) 점프**이고, `setjmp/longjmp`는 콜 스택을 거슬러 다른 함수로 이동할 수 있는 **비지역(Non-local) 점프**임.
    
    ### 핵심 차이점 비교
    
    | **구분** | **goto** | **setjmp / longjmp** |
    | --- | --- | --- |
    | **동작 범위** | 같은 함수 내부 (Local) | 호출 스택(Call Stack) 상의 다른 함수 (Non-local) |
    | **동작 원리** | 컴파일 타임에 결정된 주소로 PC(Program Counter)만 단순 변경 | 런타임에 CPU 레지스터 상태(SP, PC 등)를 저장(`jmp_buf`)하고 복원 |
    | **주요 용도** | 다중 루프 단번에 탈출, 함수 내 공통 자원 해제(Cleanup) | 깊은 콜 스택에서의 예외(Exception) 처리, 코루틴/스케줄러 구현 |
    | **스택 상태** | 변화 없음 (같은 스택 프레임 내 이동) | 복귀하는 지점(`setjmp`) 이후에 쌓인 하위 스택 프레임을 모두 폐기 |
    
    ---
    
    ### 1. 일반 `goto` 문
    
    - **제약사항:** 다른 함수로는 절대 점프할 수 없음. 컴파일러가 라벨(Label)의 위치를 같은 스택 프레임 내에서만 계산하기 때문임.
    - **비용(Overhead):** 어셈블리 레벨에서 단순한 `JMP` 명령어로 번역되므로 성능 오버헤드가 거의 없음.
    - **실무 패턴:** 리눅스 커널 등 C언어 프로젝트에서, 함수 마지막에 `free()`나 파일 닫기 코드를 모아두고 에러 발생 시 `goto cleanup;` 형태로 보내는 데 매우 유용하게 쓰임.
    
    ### 2. `setjmp` / `longjmp`
    
    - **콜 스택 점프:** `Func_A -> Func_B -> Func_C` 순서로 함수가 깊게 호출되었더라도, `Func_C`에서 `longjmp`를 호출하면 `Func_B`를 무시하고 즉시 `Func_A`의 `setjmp` 지점으로 복귀함.
    - **컨텍스트 스위칭:** `setjmp` 호출 시점의 레지스터 상태와 스택 포인터를 `jmp_buf` 메모리에 저장하는 작업이 수반되므로 `goto`보다 무거움.
    - **치명적 주의점 (메모리 누수):** C++의 `try-catch` 스택 언와인딩(Stack Unwinding) 메커니즘과 다름. 중간에 건너뛴 `Func_B`, `Func_C`에서 `malloc`으로 동적 할당한 메모리가 있거나 `fopen`으로 연 파일이 있어도 자동으로 해제해 주지 않음. 리소스 누수(Resource Leak)에 극도로 주의해야 함.
- windows/linux에서 setjmp사용
    
    윈도우(Windows) 시스템에서도 `setjmp`와 `longjmp`는 완벽하게 동작함. 이는 특정 OS(유닉스/리눅스)의 전유물이 아니라 **ANSI C 표준 라이브러리(`<setjmp.h>`)**의 일부이기 때문임. MSVC(Visual Studio), MinGW, Clang 등 윈도우용 C/C++ 컴파일러에서 모두 지원함.
    
    **윈도우 환경(MSVC) 사용 시 특징 및 주의점:**
    
    - **내부 구현 (SEH 연동):** MSVC(Microsoft Visual C++)에서 `longjmp`는 단순히 레지스터(SP, PC)만 덮어쓰는 것이 아님. 내부적으로 윈도우 OS의 고유 예외 처리 방식인 **SEH (Structured Exception Handling)** 메커니즘을 호출하여 스택을 걷어내는(Unwinding) 방식으로 안전하게 구현되어 있음.
    - **컴파일러 매크로 치환 (`_setjmp`):** 윈도우 환경의 복잡한 스택 구조(특히 보안 계층)를 안전하게 풀기 위해, MSVC는 소스코드의 `setjmp`를 OS 레벨의 스택 복원을 지원하는 `_setjmp` 또는 `_setjmp3` 내장 함수(Intrinsic)로 몰래 치환하여 컴파일함.
    - **C++과의 충돌 위험:** 순수 C 코드가 아닌 C++ 환경에서 사용할 때의 치명적 문제는 윈도우에서도 동일함. 스택을 점프하는 과정에서 지역 객체들의 **소멸자(Destructor)가 호출되지 않아 리소스 누수**가 발생함. 윈도우 환경이라도 C++ 예외(`try-catch`)나 SEH(`__try-finally`)와 `setjmp`를 혼용하는 것은 엄격히 금지됨.
