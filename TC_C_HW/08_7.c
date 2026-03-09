#include <stdio.h>

enum { N_MAX = 10 };

int main(void)
{
    int input = 0;
    int arr[N_MAX] = { 0 };

    while (scanf("%d", &input) == 1) {
        int idx = input % N_MAX;
        if (input == 0) break;

        if (idx < 0) {
            idx += N_MAX;
        }

        arr[idx]++;
    }

    for (size_t iArr = 0; iArr < N_MAX; iArr++) {
        int count = arr[iArr];
        
        if (count != 0) {
            printf("%zu : %d개\n", iArr, count);
        }
    }

    return 0;
}