#include <stdio.h>

void hanoi(int depth, int l, int m, int r)
{
    if (depth > 1) {
        hanoi(depth - 1, l, r, m);
    }

    printf("%d %d\n", l, r);

    if (depth > 1) {
        hanoi(depth - 1, m, l, r);
    }
}

int main(void)
{
    int depth;
    int repeat = 0x1;

    scanf("%d", &depth);

    repeat <<= depth;
    --repeat;

    printf("%d\n", repeat);
    hanoi(depth , 1, 2, 3);
    return 0;
}