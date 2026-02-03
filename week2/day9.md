# [2주차: 포인터와 메모리 관리 (Memory & Pointers)]
## Day 9. 제네릭 Swap 함수 (void)*
- **입력:** 두 변수의 주소 `void *a, void *b`, 데이터 크기 `size_t size`
- **출력:** 두 변수의 값이 교환됨
- **제약조건:** `malloc` 사용 금지, 바이트 단위 교환 알고리즘 사용.
- **실행결과:**

```c
=== Day 9: Generic Swap Implementation ===

[Int] Before: 10, 20
[Int] After : 20, 10

[Double] Before: 3.14159, 99.99000
[Double] After : 99.99000, 3.14159

[Struct] Before: Kim(1), Lee(2)
[Struct] After : Lee(2), Kim(1)
```

```c
// 테스트를 위한 구조체 정의
typedef struct {
    int id;
    char name[20];
    double score;
} Student;

Student s1 = {1, "Kim", 85.5};
Student s2 = {2, "Lee", 92.0};
```
---


### 코드

```c
#include <stdio.h>
#include <stdint.h>
#define type_name(expr) _Generic((expr), \
    char: "CHAR", \
    short: "SHORT", \
    int: "INT", \
    long: "LONG", \
    float: "FLOAT", \
    double: "DOUBLE", \
    char*: "STRING", \
    Student: "STRUCT", \
    default: "undefined")

/*
Day 9. 제네릭 Swap 함수 (void)*
- **입력:** 두 변수의 주소 `void *a, void *b`, 데이터 크기 `size_t size`
- **출력:** 두 변수의 값이 교환됨
- **제약조건:** `malloc` 사용 금지, 바이트 단위 교환 알고리즘 사용.
*/

// 테스트를 위한 구조체 정의
typedef struct {
    int id;
    char name[20];
    double score;
} Student;

void* Swap(void *a, void *b, size_t size){
    
    a = (char*) a;
    b = (char*) b;
    char* temp;
    
    for(int i=0;i<size;i++){
        temp=a;
        a=b;
        b=temp;

        a++;
        b++;
    }

    printf("[%s] SWAP  : %d, %d\n",type_name((int)a),*(int*)a,*(int*)b);
    
}

int main(){

    printf("=== Day 9: Generic Swap Implementation ===\n");
    
    Student s1 = {1, "Kim", 85.5};
    Student s2 = {2, "Lee", 92.0};
    
    int a=1,b=2;

    printf("[%s] Before: %d, %d\n",type_name(a),a,b);
    Swap(&a,&b,sizeof(int));
    printf("[%s] After : %d, %d\n",type_name(a),a,b); // ??
    


    return 0;
}
```

### 실행 결과

```bash
=== Day 9: Generic Swap Implementation ===
[INT] Before: 1, 2
[INT] SWAP  : 2, 1
[INT] After : 1, 2
[1] + Done                       "/usr/bin/gdb" --interpreter=mi --tty=${DbgTerm} 0<"/tmp/Microsoft-MIEngine-In-lvsqy4af.25q" 1>"/tmp/Microsoft-MIEngine-Out-co42yxdm.p4b”

// 수정 코드
=== Day 9: Generic Swap Implementation ===

[INT] Before: 1, 2
[INT] After : 2, 1

[DOUBLE] Before: 85.50000, 92.00000
[DOUBLE] After : 92.00000, 85.50000

[STRUCT] Before: Kim(1), Lee(2)
[STRUCT] After: Lee(2), Kim(1)

[1] + Done                       "/usr/bin/gdb" --interpreter=mi --tty=${DbgTerm} 0<"/tmp/Microsoft-MIEngine-In-fa1ezuqq.pjd" 1>"/tmp/Microsoft-MIEngine-Out-w3qveapc.ulz”
```
