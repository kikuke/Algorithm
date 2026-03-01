#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

enum { TEST_TRY_MAX = 1000000 };
enum { TEST_NUM_MAX = 6 };

inline static int get_dice(void);

int main(void)
{
    time_t tSeed = 0;
    int rand_cnt[TEST_NUM_MAX * 2] = { 0 };

    if ((tSeed = time(0)) == (time_t)-1) {
        fprintf(stderr, "time() error occurred with %s", strerror(errno));
        return -1;
    }
    srand((unsigned int)tSeed);

    for (size_t iTest = 0; iTest < TEST_TRY_MAX; iTest++) {
        int _result = get_dice() + get_dice();
        rand_cnt[_result]++;
    }

    for (size_t iRes = 0; (iRes < (TEST_NUM_MAX * 2) - 1); iRes++) {
        double prob = (((double)rand_cnt[iRes] / (double)TEST_TRY_MAX) * 100.0);
        printf("%d probability: %.2f\n", iRes + 2, prob);
    }

    return 0;
}

static int get_dice(void)
{
    return (rand() % TEST_NUM_MAX);
}
