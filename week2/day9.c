#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

enum op_id // ? if switch 안쓰면 왜 쓰지
{
    Add,
    Sub,
    Mul,
    Div,
    Exit
};

int func(int (*fp)(int, int))
{
    
    int a, b, res, sel;
    printf("Select (0:Add, 1:Sub, 2:Mul, 3:Div, 4:Exit): ");
    scanf("%d", &sel);

    printf("Input two integers: ");
    scanf("%d %d", &a, &b);
    res = fp(a, b);

    return res;
}

int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
int mul(int a, int b) { return a * b; }
int div(int a, int b) { return a / b; }
int exit(int a, int b) { return 0; }

int main()
{
    int res;
    int (*fp)(int, int);
    printf("=== Day 11: Function Pointer Array Calculator ===\n\n");

    fp=add;
    res = func(fp);
    printf(">> Result: %d\n\n", res);

    fp=sub;
    res = func(fp);
    printf(">> Result: %d\n\n", res);

    fp=mul;
    res = func(fp);
    printf(">> Result: %d\n\n", res);

    fp=div;
    res = func(fp);
    printf(">> Result: %d\n\n", res);

    fp=exit;
    printf("Select (0:Add, 1:Sub, 2:Mul, 3:Div, 4:Exit): ");
    scanf("%d", &res);

    return 0;
}