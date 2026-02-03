# C Programming Exercises

임베디드 시스템 개발을 위한 C 언어 학습 과제 모음입니다.  
비트 조작, 메모리 관리, 자료구조, 시스템 프로그래밍 등 실무에서 필요한 핵심 개념을 다룹니다.
개인 과제 정리하는 용도이기 때문에 정답은 틀리는 경우가 많습니다!

## 📚 과제 구성

### Week 1: 비트 연산과 데이터 표현
- **Day 1**: 비트 제어 매크로 (SET/CLEAR/TOGGLE)
- **Day 2**: Endianness 변환 (Network ↔ Host)
- **Day 3**: RGB565 패킹 데이터 파싱
- **Day 4**: 비트 순서 반전 (Mirroring)
- **Day 5**: Population Count (1의 개수 세기)
- **Day 6**: 원형 비트 시프트 (Rotate)
- **Day 7**: XOR Checksum 계산

### Week 2: 포인터와 메모리 관리
- **Day 8**: 안전한 Memcpy (Overlap 처리)
- **Day 9**: 제네릭 Swap 함수 (`void*`)
- **Day 10**: 2차원 배열 동적 할당
- **Day 11**: 함수 포인터 배열 계산기
- **Day 12**: `offsetof` 매크로 구현
- **Day 13**: 고정 크기 메모리 풀 (Memory Pool)
- **Day 14**: Hexdump 유틸리티

### Week 3: 임베디드 자료구조
- **Day 15**: 원형 버퍼 (Ring Buffer) 구현

## 🎯 학습 목표

이 과제들은 단순히 "동작하는 코드"를 넘어 다음을 중점적으로 학습합니다:

- ✅ **메모리 효율성**: 최소한의 메모리로 최대 성능
- ✅ **포인터 안정성**: 메모리 오류 및 누수 방지
- ✅ **비트 연산 최적화**: 하드웨어 제어를 위한 효율적 구현
- ✅ **임베디드 실무 대비**: 실제 개발에서 사용하는 기법

## 🔧 개발 환경

```bash
# 컴파일
gcc dayX.c -o dayX

# 실행
./dayX
```

## 📁 디렉토리 구조

```
.
├── week1/          # 비트 연산 과제
│   ├── day1.c
│   ├── day2.c
│   └── ...
├── week2/          # 메모리 관리 과제
│   ├── day8.c
│   ├── day9.c
│   └── ...
├── week3/          # 자료구조 과제
│   └── day15.c
└── main.c          # 통합 테스트
```

## 💡 주요 기술

### 비트 연산
```c
SET_BIT(x, n)    // n번째 비트를 1로
CLEAR_BIT(x, n)  // n번째 비트를 0으로
TOGGLE_BIT(x, n) // n번째 비트 반전
```

### 메모리 관리
```c
// 2D 배열 동적 할당 (연속 메모리)
int **matrix = alloc_2d(rows, cols);

// 메모리 풀 할당
void *ptr = pool_alloc(&my_pool);
pool_free(&my_pool, ptr);
```

### 자료구조
```c
// 원형 버퍼 (FIFO)
rb_put(&buffer, data);
rb_get(&buffer, &data);
```

## 📝 작성 규칙

### 코드 스타일 < 맞추려 최대한 노력할 것
- 변수명: `snake_case`
- 함수명: `snake_case`
- 매크로: `UPPER_CASE`
- 구조체: `PascalCase`

### 제약 조건
- **표준 라이브러리 최소 사용**: 직접 구현 우선
- **메모리 누수 금지**: Valgrind 검증 필수
- **매직 넘버 금지**: `#define` 사용
- **주석 필수**: 복잡한 로직은 설명 추가
- 등등 ....
- 
## 🔍 테스트 도구

### GDB (디버깅)
```bash
gcc -g day1.c -o day1
gdb ./day1
```

## 📖 참고 자료

- [The C Programming Language (K&R)](https://en.wikipedia.org/wiki/The_C_Programming_Language)
- [Effective C](https://nostarch.com/Effective_C)
- Linux Kernel Coding Style

## 🤝 기여

버그 발견이나 개선 사항이 있다면 이슈나 PR을 남겨주세요!

## 📜 라이선스

MIT License

---

**Happy Coding! 🚀**
