#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <time.h>

enum { TEST_NUM_MAX = 10 };

/* 구조체로 묶기 */
static int32_t rem_card = TEST_NUM_MAX;
static uint8_t check[TEST_NUM_MAX];

static int get_card(void);

int main(void)
{
    time_t tSeed = 0;

    if ((tSeed = time(0)) == (time_t)-1) {
        fprintf(stderr, "time failed by %s\n", strerror(errno));
        return 1;
    }
    srand((unsigned int)tSeed);

    for (size_t iTry = 0; iTry < TEST_NUM_MAX; iTry++) {
        printf("%zu Card: %d\n", iTry, get_card());
    }

    return 0;
}

static int get_card(void)
{
    int _card = 0;

    if (rem_card <= 0) {
        return -1;
    }

    while (check[(_card = (rand() % TEST_NUM_MAX))] != 0);  /* 반복 시도가 아닌 카드풀에서 추출하기 */

    rem_card--;
    check[_card] = 1;
    return _card + 1;
}

