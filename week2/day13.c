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
void pool_init(MemoryPool* pool) 
{
    
    for(int i=0;i<POOL_SIZE*BLOCK_SIZE;i=i+32){
        (pool->free_list)=&(pool->memory_area[i]);
        printf("pool->memory_area[%d]의 주소=%d\n",i,&(pool->memory_area[i]));
        printf("pool->free_list의 주소=%d\n",(pool->free_list));
    }
    
    (pool->free_list)=&(pool->memory_area[0]);
            printf("pool->free_list의 주소=%d\n",&(pool->free_list));

    printf("pool->memory_area[319]의 주소=%d\n",&(pool->memory_area[319]));
    
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

    printf("sizeof struct = %d\n",sizeof(my_pool));
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