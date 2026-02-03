# [2주차: 포인터와 메모리 관리 (Memory & Pointers)]
## Day 13. 고정 크기 메모리 풀 (Memory Pool) 할당기
- **입력:** 할당 요청
- **출력:** 할당된 메모리 블록 주소 (실패 시 NULL)
- **제약조건:** 런타임에 `malloc` 사용 금지. 미리 잡아둔 큰 배열 안에서 청크를 쪼개 줄 것.
- **2. 구현 목표**
    - **블록 크기:** 32 Bytes
    - **블록 개수:** 10개
    - **기능:** 초기화(`init`), 할당(`alloc`), 해제(`free`)
- **실행결과:**

```c
[Init] Memory Pool Initialized (10 blocks of 32 bytes)
Allocated: 0x5a6dbc0c9040, 0x5a6dbc0c9060, 0x5a6dbc0c9080
Used Blocks: 3
Freeing 0x5a6dbc0c9060...
Re-allocated: 0x5a6dbc0c9060 (Should be same as old p2)

```

- 프로그램 기본 구조
    
    ```c
    #include <stdio.h>
    #include <stdint.h>
    #include <stdbool.h>
    
    // 설정: 블록 크기와 개수
    #define BLOCK_SIZE  32
    #define POOL_SIZE   10
    
    // 메모리 블록 구조체 (Free List 관리를 위한 연결 리스트 노드)
    // 할당되지 않았을 때는 다음 빈 블록을 가리키는 포인터로 사용됨
    typedef struct Block {
        struct Block* next;
    } Block;
    
    // 메모리 풀 컨텍스트
    typedef struct {
        // 실제 메모리 공간 (바이트 배열)
        // 정렬(Alignment)을 위해 uint64_t나 align 속성을 사용할 수 있음
        uint8_t memory_area[POOL_SIZE * BLOCK_SIZE]; 
        
        // 현재 사용 가능한 첫 번째 블록을 가리키는 포인터
        Block* free_list;
        
        // 디버깅용: 현재 사용 중인 블록 수
        int used_count;
    } MemoryPool;
    
    // 전역 풀 인스턴스
    MemoryPool my_pool;
    
    // 1. 초기화: 모든 메모리를 쪼개서 연결 리스트로 연결
    void pool_init(MemoryPool* pool) {
    
    }
    
    // 2. 할당: Free List의 헤드(Head)를 떼어줌 (Pop)
    void* pool_alloc(MemoryPool* pool) {
    
    }
    
    // 3. 해제: 반환된 블록을 Free List의 헤드에 다시 붙임 (Push)
    void pool_free(MemoryPool* pool, void* ptr) {
    
    }
    
    // 테스트 코드
    int main() {
        pool_init(&my_pool);
    
        // 3개 할당
        void* p1 = pool_alloc(&my_pool);
        void* p2 = pool_alloc(&my_pool);
        void* p3 = pool_alloc(&my_pool);
    
        printf("Allocated: %p, %p, %p\n", p1, p2, p3);
        printf("Used Blocks: %d\n", my_pool.used_count);
    
        // 1개 해제 (p2)
        printf("Freeing %p...\n", p2);
        pool_free(&my_pool, p2); // 이제 p2가 free_list의 head가 됨
        
        // 다시 1개 할당 (p2와 같은 주소가 나와야 함 - LIFO 특성)
        void* p4 = pool_alloc(&my_pool);
        printf("Re-allocated: %p (Should be same as old p2)\n", p4);
    
        return 0;
    }
    ```
    
### 참고
- 구조체 안에 링크드 리스트  vs 링크드 리스트 안에 구조체

- ## 1. 구조체 안에 링크드 리스트 (Linked List inside Struct)

일반적으로 **컴포지션(Composition)** 방식입니다. 특정 객체가 자신의 멤버로 리스트 헤더나 노드를 소유하는 형태입니다.

- **구조:** `struct Session { int id; List<Message> messages; };`
- **특징:** * **논리적 포함 관계:** "세션 하나가 여러 메시지를 가진다"는 개념을 직관적으로 표현합니다.
    - **캡슐화:** 객체 내부에서 리스트의 생명주기를 관리하기 용이합니다.
    - **복합 데이터:** 객체 자체가 리스트의 '관리자' 역할을 수행할 때 적합합니다.

---

## 2. 링크드 리스트 안에 구조체 (Struct inside Linked List)

일반적으로 **노드 기반 저장(Node-based Storage)** 방식입니다. 리스트의 데이터 필드에 구조체 인스턴스가 들어가는 형태입니다.

- **구조:** `struct Node { Session data; Node* next; };`
- **특징:**
    - **데이터 중심:** 동일한 타입의 구조체들을 단순히 나열하거나 큐/스택으로 관리할 때 사용합니다.
    - **메모리 파편화:** 각 노드가 `malloc` 등으로 개별 할당될 경우, 구조체 데이터들이 메모리상에 흩어져 **Cache Miss**가 빈번해질 수 있습니다.
    - **유연성:** 데이터의 삽입과 삭제가 빈번한 동적 집합에 유리합니다.

---

## 3. 시니어 레벨에서의 핵심 비교 (Memory & Performance)

| **구분** | **구조체 내 리스트** | **리스트 내 구조체** |
| --- | --- | --- |
| **메모리 배치** | 리스트 헤더만 구조체에 포함됨 | 데이터와 포인터가 하나의 노드로 묶임 |
| **캐시 효율** | 헤더 접근은 빠르나 노드 순회 시 이산적 | 노드 접근 시 포인터와 데이터가 인접함 |
| **추구 방향** | **객체 지향적** (소유권 중심) | **데이터 지향적** (흐름 중심) |
| **임베디드/C** | 주로 `Intrusive List` 사용 (아래 설명) | 표준적인 라이브러리 방식 (`std::list`) |

---

## 4. 실무적 권장: Intrusive Linked List (침투형 리스트)

커널 프로그래밍이나 고성능 시스템에서는 **구조체 안에 리스트 노드**를 박아넣는 방식을 선호합니다. (예: Linux Kernel의 `struct list_head`)

C

```bash
struct User {
    int id;
    char name[32];
    struct list_node node; // 구조체 내부에 링크 노드 포함
};
```

- **장점:** 1. 데이터와 링크가 동일한 메모리 블록에 있어 캐시 적중률이 높습니다.
    
    2.  추가적인 노드 할당 오버헤드가 없습니다.
    
    3.  하나의 객체가 여러 개의 리스트(예: 정렬 기준이 다른 리스트들)에 동시에 포함될 수 있습니다.
    

### 요약

- **추상화와 관리 편의성**이 중요하다면 **구조체 안에 리스트**를 두어 소유 관계를 명확히 하십시오.
- **성능과 메모리 제어**가 중요하다면 **Intrusive 방식**(구조체 안에 노드 배치)을 사용하여 데이터와 포인터를 물리적으로 인접시키십시오.

---


### 코드 (다시 해야함.. 이번 문제 무조건 이해할 것)

```c
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/*
- ** Day 13. 고정 크기 메모리 풀 (Memory Pool) 할당기 **
    - **입력:** 할당 요청
    - **출력:** 할당된 메모리 블록 주소 (실패 시 NULL)
    - **제약조건:** 런타임에 `malloc` 사용 금지. 미리 잡아둔 큰 배열 안에서 청크를 쪼개 줄 것.
    - **2. 구현 목표**
        - **블록 크기:** 32 Bytes
        - **블록 개수:** 10개
        - **기능:** 초기화(`init`), 할당(`alloc`), 해제(`free`)
*/

// 설정: 블록 크기와 개수
#define BLOCK_SIZE  32
#define POOL_SIZE   10

// 메모리 블록 구조체 (Free List 관리를 위한 연결 리스트 노드)
// 할당되지 않았을 때는 다음 빈 블록을 가리키는 포인터로 사용됨
typedef struct Block {
    struct Block* next;
} Block;

// 메모리 풀 컨텍스트
typedef struct {
    // 실제 메모리 공간 (바이트 배열)
    // 정렬(Alignment)을 위해 uint64_t나 align 속성을 사용할 수 있음
    uint8_t memory_area[POOL_SIZE * BLOCK_SIZE]; 
    
    // 현재 사용 가능한 첫 번째 블록을 가리키는 포인터
    Block* free_list;
    
    // 디버깅용: 현재 사용 중인 블록 수
    int used_count;
} MemoryPool;

// 전역 풀 인스턴스
MemoryPool my_pool;

// 1. 초기화: 모든 메모리를 쪼개서 연결 리스트로 연결
void pool_init(MemoryPool* pool) {
    
    for(int i=0;i<POOL_SIZE*BLOCK_SIZE;i++){
        pool->memory_area[i]+=0x20;
        pool->free_list=pool->memory_area[i];
    }
}

// 2. 할당: Free List의 헤드(Head)를 떼어줌 (Pop)
void* pool_alloc(MemoryPool* pool) {
    pool->free_list=pool->memory_area[pool->used_count];
    pool->used_count++;
    
}

// 3. 해제: 반환된 블록을 Free List의 헤드에 다시 붙임 (Push)
void pool_free(MemoryPool* pool, void* ptr) {
    ptr=pool->memory_area[(pool->used_count)+1];
    pool->used_count--;
}

// 테스트 코드
int main() {
    pool_init(&my_pool);

    // 3개 할당
    void* p1 = pool_alloc(&my_pool);
    void* p2 = pool_alloc(&my_pool);
    void* p3 = pool_alloc(&my_pool);

    printf("[Init] Memory Pool Initialized (10 blocks of 32 bytes)");
    printf("Allocated: %p, %p, %p\n", p1, p2, p3);
    printf("Used Blocks: %d\n", my_pool.used_count);

    // 1개 해제 (p2)
    printf("Freeing %p...\n", p2);
    pool_free(&my_pool, p2); // 이제 p2가 free_list의 head가 됨
    
    // 다시 1개 할당 (p2와 같은 주소가 나와야 함 - LIFO 특성)
    void* p4 = pool_alloc(&my_pool);
    printf("Re-allocated: %p (Should be same as old p2)\n", p4);

    return 0;
}
```

### 실행 결과

```bash
[Init] Memory Pool Initialized (10 blocks of 32 bytes)Allocated: 0x555555558040, 0x555555558040, 0x555555558040
Used Blocks: 0
Freeing 0x555555558040...
Re-allocated: 0x555555558040 (Should be same as old p2)
[1] + Done                       "/usr/bin/gdb" --interpreter=mi --tty=${DbgTerm} 0<"/tmp/Microsoft-MIEngine-In-c15fhhuh.gqn" 1>"/tmp/Microsoft-MIEngine-Out-tvmtb2rh.3tf”

[1] + Done                       "/usr/bin/gdb" --interpreter=mi --tty=${DbgTerm} 0<"/tmp/Microsoft-MIEngine-In-4lt3zj1c.opv" 1>"/tmp/Microsoft-MIEngine-Out-0a53ylnp.nxn”
```
