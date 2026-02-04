# [3주차: 임베디드 필수 자료구조 (Data Structures)]
## Day 15. 원형 버퍼 (Ring Buffer) 구현
- **입력:** 데이터 Push/Pop , Dnque/Deque요청
- **출력:** 버퍼 상태 (Full/Empty), 꺼낸 데이터
- **제약조건:** 배열로 구현, Head/Tail 인덱스 관리, 오버플로우 방지 로직.
- **실행결과:**

```c
-- Phase 1: Filling Buffer ---
Put: 1 (Head: 1, Tail: 0)
Put: 2 (Head: 2, Tail: 0)
Put: 3 (Head: 3, Tail: 0)
Put: 4 (Head: 4, Tail: 0)
Put: 5 (Head: 5, Tail: 0)
Put: 6 (Head: 6, Tail: 0)
Put: 7 (Head: 7, Tail: 0)
Fail to Put: 8 (Buffer Full!)

--- Phase 2: Reading Buffer ---
Get: 1 (Head: 7, Tail: 1)
Get: 2 (Head: 7, Tail: 2)
Get: 3 (Head: 7, Tail: 3)

--- Phase 3: Writing again (Wrap around) ---
Put: 99 (Head: 0, Tail: 3)

```

- 참고
    
    ### 1. 핵심 개념: 꼬리가 머리를 쫓는다
    
    원형 버퍼는 물리적으로는 선형(일자) 메모리 배열이지만, 논리적으로는 끝과 시작이 연결된 **원형(Circle)** 형태를 가집니다.
    
    - **FIFO (First-In, First-Out):** 먼저 들어온 데이터가 먼저 나갑니다.
    - **Head (Write Pointer):** 데이터를 **넣는(Put)** 위치. (Producer)
    - **Tail (Read Pointer):** 데이터를 **꺼내는(Get)** 위치. (Consumer)
    - **Wrap Around:** 인덱스가 배열 끝에 도달하면 다시 0번 인덱스로 돌아갑니다.
    
    ### 중요: '가득 참(Full)'과 '비어 있음(Empty)' 구분
    
    가장 흔한 구현 방식은 **"배열의 한 칸을 일부러 비워두는 것"**입니다.
    
    - **Empty:** `Head == Tail`
    - **Full:** `(Head + 1) % Size == Tail` (Head가 Tail 바로 뒤까지 쫓아왔을 때)
    - 이렇게 하지 않으면 `Head == Tail`인 상태가 '비어있는지' '꽉 찼는지' 구분하기 위해 별도의 플래그 변수가 필요합니다. 여기서는 **한 칸 비우는 방식**을 씁니다.
    
    ---
    
    ### 2. 구현 목표
    
    - **구조체 기반:** 여러 개의 버퍼를 관리할 수 있도록 객체지향적으로 설계.
    - **기능:** `put` (데이터 넣기), `get` (데이터 꺼내기), `is_full`, `is_empty`.
    
    <img width="1492" height="941" alt="image" src="https://github.com/user-attachments/assets/12fc7cc4-01c7-4f17-81b9-728ed3f0099a" />

    
    ```c
    // ---- 테스트 코드 ----
    int main() {
        RingBuffer uart_rx_buf;
        uint8_t temp;
    
        rb_init(&uart_rx_buf);
    
        printf("--- Phase 1: Filling Buffer ---\n");
        // 버퍼 사이즈가 8이므로, 한 칸 비우면 최대 7개 저장 가능
        for (int i = 1; i <= 8; i++) {
            if (rb_put(&uart_rx_buf, i)) {
                printf("Put: %d (Head: %d, Tail: %d)\n", i, uart_rx_buf.head, uart_rx_buf.tail);
            } else {
                printf("Fail to Put: %d (Buffer Full!)\n", i);
            }
        }
    
        printf("\n--- Phase 2: Reading Buffer ---\n");
        // 3개만 읽어봄
        for (int i = 0; i < 3; i++) {
            if (rb_get(&uart_rx_buf, &temp)) {
                printf("Get: %d (Head: %d, Tail: %d)\n", temp, uart_rx_buf.head, uart_rx_buf.tail);
            }
        }
    
        printf("\n--- Phase 3: Writing again (Wrap around) ---\n");
        // 읽어서 공간이 생겼으므로 다시 쓰기 가능 (인덱스가 0으로 돌아가는지 확인)
        if (rb_put(&uart_rx_buf, 99)) {
             printf("Put: 99 (Head: %d, Tail: %d)\n", uart_rx_buf.head, uart_rx_buf.tail);
        }
    
        return 0;
    }
    ```

---


### 코드

```c

// head, tail값은 index로 넣어줘야함. 다시 수정할 것

#include <stdio.h>
#include <stdint.h>
#define SIZE 8

typedef struct RingBuffer{
    int head;
    int tail;
    int RingArr[SIZE];
}RingBuffer;

void rb_init(RingBuffer* buffer)
{
    for(int i=0;i<SIZE;i++) (buffer->RingArr[i])=0;
    buffer->head=0;
    buffer->tail=0;
    //for(int i=0;i<8;i++) printf("i=%d, RingArr=%d\n",i+1,buffer->RingArr[i]);
}
int rb_put(RingBuffer* buffer, int i)
{
    if(((buffer->head)+1)%SIZE==(buffer->tail))
    {
        return 0;
    }
    else
    {
        buffer->head ++;
        buffer->RingArr[i]=buffer->head;
        if((buffer->head)==8)
        {
            buffer->head=0;
        }
        return 1;
    }
}
int rb_get(RingBuffer* buffer, int i)
{
    if(buffer->RingArr[i]==buffer->RingArr[(i+1)%8])
    {
        return 0;
    }
    else
    {
        buffer->tail++;
        return buffer->tail;
    }
    
}

int main() 
{
    RingBuffer uart_rx_buf;
    uint8_t temp;

    rb_init(&uart_rx_buf);

    printf("--- Phase 1: Filling Buffer ---\n");
    // 버퍼 사이즈가 8이므로, 한 칸 비우면 최대 7개 저장 가능
    for (int i = 1; i <= 8; i++) 
    {
        if (rb_put(&uart_rx_buf, i)) 
        {
            printf("Put: %d (Head: %d, Tail: %d)\n", i, uart_rx_buf.head, uart_rx_buf.tail);
        } 
        else 
        {
            printf("Fail to Put: %d (Buffer Full!)\n", i);
        }
    }

    printf("\n--- Phase 2: Reading Buffer ---\n");
    for (int i = 1; i <= 3; i++) 
    {
        if (rb_get(&uart_rx_buf, 3)) 
        {
            printf("Get: %d (Head: %d, Tail: %d)\n", i, uart_rx_buf.head, uart_rx_buf.tail);
        } 
        else 
        {
            printf("Fail to Get: %d (Buffer empty!)\n", i);
        }
    }


    printf("\n--- Phase 3: Writing again (Wrap around) ---\n");
    // 읽어서 공간이 생겼으므로 다시 쓰기 가능 (인덱스가 0으로 돌아가는지 확인)
    if (rb_put(&uart_rx_buf, 99)) 
    {
         printf("Put: 99 (Head: %d, Tail: %d)\n", uart_rx_buf.head, uart_rx_buf.tail);
    }

    return 0;
}



```

### 실행 결과

```bash
--- Phase 1: Filling Buffer ---
Put: 1 (Head: 1, Tail: 0)
Put: 2 (Head: 2, Tail: 0)
Put: 3 (Head: 3, Tail: 0)
Put: 4 (Head: 4, Tail: 0)
Put: 5 (Head: 5, Tail: 0)
Put: 6 (Head: 6, Tail: 0)
Put: 7 (Head: 7, Tail: 0)
Fail to Put: 8 (Buffer Full!)

--- Phase 2: Reading Buffer ---
Get: 1 (Head: 7, Tail: 1)
Get: 2 (Head: 7, Tail: 2)
Get: 3 (Head: 7, Tail: 3)

--- Phase 3: Writing again (Wrap around) ---
Put: 99 (Head: 0, Tail: 3)
[1] + Done                       "/usr/bin/gdb" --interpreter=mi --tty=${DbgTerm} 0<"/tmp/Microsoft-MIEngine-In-0nggds5r.aof" 1>"/tmp/Microsoft-MIEngine-Out-2gvj2zl1.zkn”
```
