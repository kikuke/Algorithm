#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>

enum { TEST_RAND_TRY_MAX = 30 };
enum { TEST_RAND_VALUE_MIN = 1, TEST_RAND_VALUE_MAX = 6 };

int main(void)
{
    time_t tSeed = 0;
    int rand_num = 0;

    int result = 0;

    if ((tSeed = time(0)) == (time_t)-1) {
        fprintf(stderr, "Error is Occurred in time()\n");
        return -1;
    }
    srand((unsigned int)tSeed);

    for (size_t iRand = 0; iRand < TEST_RAND_TRY_MAX; iRand++) {
        rand_num = rand();
        result = (rand_num % (TEST_RAND_VALUE_MAX - TEST_RAND_VALUE_MIN + 1)) + TEST_RAND_VALUE_MIN;
        printf("%d ", result);
    }
    printf("\n");

    return 0;
}