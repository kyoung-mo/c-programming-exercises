# [3주차: 임베디드 필수 자료구조 (Data Structures)]
## Day 18. 우선순위 큐 (Min Heap) - 태스크 스케줄링용
- **입력:** (TaskID, Priority) 쌍 삽입, Pop 요청
- **출력:** 우선순위가 가장 높은(숫자가 낮은) TaskID 반환
- **제약조건:** 배열 기반 힙 구현.
- **실행결과:**

```c
=== Day 18: Task Scheduler (Min Heap) ===

Tasks pushed: (1, 50), (2, 10), (3, 5), (4, 100), (5, 0)
Processing Tasks...

>> Executing Task 5 (Priority 0)
>> Executing Task 3 (Priority 5)
>> Executing Task 2 (Priority 10)
>> Executing Task 1 (Priority 50)
>> Executing Task 4 (Priority 100)
```

---


### 코드

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct MinHeap {
    int taskid;
    int priority;
} task;

task heap[100];
int heap_size = 0;

void swap(task *a, task *b) {
    task temp = *a;
    *a = *b;
    *b = temp;
}

void push_queue(int id, int pri) {
    task new_task;
    new_task.taskid = id;
    new_task.priority = pri;
    
    heap[heap_size] = new_task;
    int current = heap_size;
    heap_size++;
    
    // 상향 조정 (heapify up)
    while(current > 0) {
        int parent = (current - 1) / 2;
        if(heap[current].priority < heap[parent].priority) {
            swap(&heap[current], &heap[parent]);
            current = parent;
        } else {
            break;
        }
    }
}

task pop_queue() {
    task min_task = heap[0];
    
    heap_size--;
    heap[0] = heap[heap_size];
    
    // 하향 조정 (heapify down)
    int current = 0;
    while(1) {
        int left = 2 * current + 1;
        int right = 2 * current + 2;
        int smallest = current;
        
        if(left < heap_size && heap[left].priority < heap[smallest].priority) {
            smallest = left;
        }
        if(right < heap_size && heap[right].priority < heap[smallest].priority) {
            smallest = right;
        }
        
        if(smallest != current) {
            swap(&heap[current], &heap[smallest]);
            current = smallest;
        } else {
            break;
        }
    }
    
    return min_task;
}

int main() {
    printf("=== Day 18: Task Scheduler (Min Heap) ===\n\n");
    
    push_queue(1, 50);
    push_queue(2, 10);
    push_queue(3, 5);
    push_queue(4, 100);
    push_queue(5, 0);
    
    printf("Tasks pushed: (1, 50), (2, 10), (3, 5), (4, 100), (5, 0)\n");
    printf("Processing Tasks...\n\n");
    
    while(heap_size > 0) {
        task t = pop_queue();
        printf(">> Executing Task %d (Priority %d)\n", t.taskid, t.priority);
    }
    
    printf("\n");
    
    return 0;
}
```

### 실행 결과

```bash
=== Day 18: Task Scheduler (Min Heap) ===

Tasks pushed: (1, 50), (2, 10), (3, 5), (4, 100), (5, 0)
Processing Tasks...

>> Executing Task 5 (Priority 0)
>> Executing Task 3 (Priority 5)
>> Executing Task 2 (Priority 10)
>> Executing Task 1 (Priority 50)
>> Executing Task 4 (Priority 100)

[1] + Done                       "/usr/bin/gdb" --interpreter=mi --tty=${DbgTerm} 0<"/tmp/Microsoft-MIEngine-In-jimwpajt.coa" 1>"/tmp/Microsoft-MIEngine-Out-wbyrtfpn.1pz”
```
