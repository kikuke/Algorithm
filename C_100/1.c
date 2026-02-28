#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <limits.h>

enum { TEST_INPUT_MAX = 10 };

int main(void)
{
    int nMin = INT_MAX, nMax = INT_MIN;
    int64_t nSum = 0;
    double nAvg = 0.0;

    for (size_t iNum = 0; iNum < TEST_INPUT_MAX; iNum++) {
        int input = 0;

        if (scanf("%d", &input) != 1) {
            fprintf(stderr, "input error occurred in %zu input.\n", iNum);
            return 1;
        }

        nSum += input;
        
        if (nMin > input) nMin = input;
        if (nMax < input) nMax = input;
    }
    nAvg = ((double)nSum) / (double)TEST_INPUT_MAX;

    printf("min: %d\nmax: %d\navg: %.2f\n", nMin, nMax, nAvg);

    return 0;
}
