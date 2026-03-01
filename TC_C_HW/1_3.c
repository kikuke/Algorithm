#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(void)
{
    int input = 0;
    int count = 0;

    if (scanf("%d", &input) != 1) {
        fprintf(stderr, "Error is Occurred by %s\n", strerror(errno));
    }

    while (input > 0) {
        input /= 10;
        count++;
    }

    printf("%d\n", count);

    return 0;
}