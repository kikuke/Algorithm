#include <stdio.h>

int main(void)
{
    int sRes = 0;
    int input = 0;
    int sum = 0;

    while ((sRes = scanf("%d", &input)) == 1) {
        if (input == 0) {
            break;
        }
        if (input > 0) {
            sum += input;
        }
    }

    printf("%d\n", sum);

    return 0;
}