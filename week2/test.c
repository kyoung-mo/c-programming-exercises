#include <stdio.h>

#define POOL_SIZE 10
#define BLOCK_SIZE 32

typedef struct {
    char memory_area[320];
    char* free_list;
} MemoryPool;

int main() {
    MemoryPool pool;
    
    printf("=== 루프 시작 ===\n");
    for(int i = 0; i < POOL_SIZE * BLOCK_SIZE; i += 32) {
        pool.free_list = &(pool.memory_area[i]);
        printf("i=%3d → free_list = %p (memory_area[%d])\n", 
               i, pool.free_list, i);
    }
    printf("=== 루프 끝 ===\n");
    printf("최종 free_list: %p\n", pool.free_list);
    
    return 0;
}