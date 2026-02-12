# [3주차: 임베디드 필수 자료구조 (Data Structures)]
## Day 21. 유한상태 머신 (FSM) - 함수 포인터 활용
- **입력:** 이벤트(버튼 클릭, 타임아웃 등)
- **출력:** 상태 전이 로그 및 액션 실행
- **제약조건:** `switch-case` 대신 상태별 구조체와 함수 포인터 테이블 사용.
- **실행결과:** `IDLE ->(Button) -> RUN`

```c
=== Day 21: Visual FSM Implementation ===
Initial State: [IDLE]

--------------------------------------------------
[TRANSITION] IDLE --(EVT_BUTTON_PRESS)--> RUN
--------------------------------------------------
   (Running... Motor spinning ⚙️)
--------------------------------------------------
[TRANSITION] RUN --(EVT_TIMEOUT)--> IDLE
--------------------------------------------------
--------------------------------------------------
[TRANSITION] IDLE --(EVT_BUTTON_PRESS)--> RUN
--------------------------------------------------
--------------------------------------------------
[TRANSITION] RUN --(EVT_RESET)--> ERROR
--------------------------------------------------
   (Waiting... ⚠️ System Halted)
--------------------------------------------------
[TRANSITION] ERROR --(EVT_RESET)--> IDLE
--------------------------------------------------

>> Simulation Ended.
```

<img width="1200" height="800" alt="image" src="https://github.com/user-attachments/assets/f40049f2-1a56-4f72-be97-c6ef68ac46aa" />


- 참고
    
    임베디드 시스템 펌웨어의 꽃인 **유한 상태 머신(FSM, Finite State Machine)**을 구현하는 것입니다.
    `switch (state) { case ... }` 로 도배된 "스파게티 코드"를 탈피하고, **함수 포인터 테이블**을 사용해 **구조적이고 확장이 쉬운 FSM**을 만드는 것이 핵심입니다.
    
    ---
    
    ### 1. 핵심 원리: 테이블 기반 FSM (Table-Driven FSM)
    
    상태(State)를 배열의 **인덱스**로, 행동(Action)을 **함수 포인터**로 매핑합니다.
    메인 루프는 현재 상태가 누구인지 알 필요 없이, 그저 **"현재 상태의 함수를 실행해라"**라고 명령만 내리면 됩니다.
    
    **그림의 핵심 논리:**
    
    1. **IDLE ↔ RUN:** 버튼(`BUTTON_PRESS`)으로 켜고, 타임아웃(`TIMEOUT`)으로 꺼집니다.
    2. **RUN → ERROR:** 실행 중 리셋(`RESET`) 신호가 오면 에러로 빠집니다.
    3. **ERROR → IDLE:** 에러 상태에서 리셋(`RESET`) 신호가 오면 초기화(IDLE)됩니다.

---


### 코드

```c
#include <stdio.h>
#include <string.h>

/* States */
enum { IDLE, RUN, ERROR, NUM_STATES };

/* Events */
enum { EVT_BUTTON_PRESS, EVT_TIMEOUT, EVT_RESET, NUM_EVENTS };

/* State/Event name strings */
const char *state_names[] = { "IDLE", "RUN", "ERROR" };
const char *event_names[] = { "EVT_BUTTON_PRESS", "EVT_TIMEOUT", "EVT_RESET" };

/*
  제약조건: switch-case 대신 상태별 함수 포인터 테이블 사용

  전이 규칙:
  IDLE  -> RUN   (EVT_BUTTON_PRESS)
  RUN   -> IDLE  (EVT_TIMEOUT)
  RUN   -> ERROR (EVT_RESET)
  ERROR -> IDLE  (EVT_RESET)
*/

/* === 상태별 액션 함수 === */
void action_idle(void) {
}

void action_run(void) {
    printf("   (Running... Motor spinning ⚙️)\n");
}

void action_error(void) {
    printf("   (Waiting... ⚠️ System Halted)\n");
}

/* === 함수 포인터 테이블: 상태 진입 시 액션 === */
void (*state_actions[NUM_STATES])(void) = {
    action_idle,
    action_run,
    action_error
};

/* === 전이 테이블: [현재상태][이벤트] = 다음상태 (-1 = 무효) === */
int transition_table[NUM_STATES][NUM_EVENTS] = {
    /* IDLE  */ { RUN,  -1,   -1    },
    /* RUN   */ { -1,   IDLE, ERROR },
    /* ERROR */ { -1,   -1,   IDLE  }
};

/* === FSM 구조체 === */
typedef struct {
    int current_state;
} FSM;

void fsm_init(FSM *fsm) {
    fsm->current_state = IDLE;
}

int fsm_handle_event(FSM *fsm, int event) {
    int next = transition_table[fsm->current_state][event];
    if (next == -1) {
        printf("[INVALID] No transition from %s on %s\n",
               state_names[fsm->current_state], event_names[event]);
        return -1;
    }

    printf("--------------------------------------------------\n");
    printf("[TRANSITION] %s --(%s)--> %s\n",
           state_names[fsm->current_state], event_names[event], state_names[next]);
    printf("--------------------------------------------------\n");

    fsm->current_state = next;
    state_actions[next]();

    return 0;
}

int main(){
    FSM fsm;
    fsm_init(&fsm);

    printf("=== Day 21: Visual FSM Implementation ===\n");
    printf("Initial State: [IDLE]\n\n");

    /* 시뮬레이션 이벤트 시퀀스 */
    int events[] = {
        EVT_BUTTON_PRESS,   /* IDLE  -> RUN   */
        EVT_TIMEOUT,         /* RUN   -> IDLE  */
        EVT_BUTTON_PRESS,   /* IDLE  -> RUN   */
        EVT_RESET,           /* RUN   -> ERROR */
        EVT_RESET            /* ERROR -> IDLE  */
    };
    int num_events = sizeof(events) / sizeof(events[0]);

    for (int i = 0; i < num_events; i++) {
        fsm_handle_event(&fsm, events[i]);
    }

    printf("\n>> Simulation Ended.\n");

    return 0;
}
```

### 실행 결과

```bash
=== Day 21: Visual FSM Implementation ===
Initial State: [IDLE]

--------------------------------------------------
[TRANSITION] IDLE --(EVT_BUTTON_PRESS)--> RUN
--------------------------------------------------
(Running... Motor spinning ⚙️)
--------------------------------------------------
[TRANSITION] RUN --(EVT_TIMEOUT)--> IDLE
--------------------------------------------------
--------------------------------------------------
[TRANSITION] IDLE --(EVT_BUTTON_PRESS)--> RUN
--------------------------------------------------
(Running... Motor spinning ⚙️)
--------------------------------------------------
[TRANSITION] RUN --(EVT_RESET)--> ERROR
--------------------------------------------------
(Waiting... ⚠️ System Halted)
--------------------------------------------------
[TRANSITION] ERROR --(EVT_RESET)--> IDLE
--------------------------------------------------

>> Simulation Ended.
[1] + Done                       "/usr/bin/gdb" --interpreter=mi --tty=${DbgTerm} 0<"/tmp/Microsoft-MIEngine-In-cq0sbg1x.q4o" 1>"/tmp/Microsoft-MIEngine-Out-r4y5sajb.1sn”
```
