# [3주차: 임베디드 필수 자료구조 (Data Structures)]
## Day 16. 단일 연결 리스트 역순 정렬
- **입력:** `1 -> 2 -> 3 -> NULL`
- **출력:** `3 -> 2 -> 1 -> NULL`
- **제약조건:** 메모리 재할당 없이 포인터 방향만 조작하여 구현.
- **실행결과:** `List Reversed.`

---


### 코드

```c
#include <stdio.h>
#include <stdlib.h>

/*
    Day 16. 단일 연결 리스트 역순 정렬
    입력:  1 -> 2 -> 3 -> NULL
    출력:  3 -> 2 -> 1 -> NULL
    조건:  메모리 재할당 없이 포인터만 변경
*/

typedef struct ListNode {
    int data;
    struct ListNode* link;
} listNode;

typedef struct {
    listNode* head;
} linkedList_h;

/* 리스트 출력 함수 */
void print_list(linkedList_h* L) {
    listNode* p = L->head;
    while (p != NULL) {
        printf("%d -> ", p->data);
        p = p->link;
    }
    printf("NULL\n");
}

/* 단일 연결 리스트 역순 함수 */
void reverse_list(linkedList_h* L) {
    listNode* prev = NULL;
    listNode* curr = L->head;
    listNode* next = NULL;

    while (curr != NULL) {
        next = curr->link;   // 다음 노드 저장
        curr->link = prev;   // 방향 뒤집기
        prev = curr;         // prev 이동
        curr = next;         // curr 이동
    }

    L->head = prev;
    printf("List Reversed.\n");
}

int main() {
    linkedList_h L;
    L.head = NULL;

    /* 노드 생성 */
    listNode* n1 = (listNode*)malloc(sizeof(listNode));
    listNode* n2 = (listNode*)malloc(sizeof(listNode));
    listNode* n3 = (listNode*)malloc(sizeof(listNode));

    /* 데이터 및 연결 */
    n1->data = 1; n1->link = n2;
    n2->data = 2; n2->link = n3;
    n3->data = 3; n3->link = NULL;

    /* head 설정 */
    L.head = n1;

    /* 출력 */
    print_list(&L);

    /* 역순 */
    reverse_list(&L);

    /* 결과 출력 */
    print_list(&L);

    return 0;
}

```

### 실행 결과

```bash
1 -> 2 -> 3 -> NULL
List Reversed.
3 -> 2 -> 1 -> NULL
[1] + Done                       "/usr/bin/gdb" --interpreter=mi --tty=${DbgTerm} 0<"/tmp/Microsoft-MIEngine-In-rkrdu0hw.jrc" 1>"/tmp/Microsoft-MIEngine-Out-ddmq2rwy.zsi”
```
