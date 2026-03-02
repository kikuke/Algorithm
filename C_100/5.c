#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

enum { TEST_CARD_TYPE = 4, TEST_CARD_NUM = 52 };

typedef struct {
    uint8_t check[TEST_CARD_NUM];
    int32_t rem_card;
} stCardManager;

static stCardManager _card_manager = { 
    .check = { 0 }, 
    .rem_card = TEST_CARD_NUM 
};

static const char _card_num[TEST_CARD_NUM / TEST_CARD_TYPE] = {
    'A', '2', '3', '4', '5', '6', '7', '8', '9', 'X', 'J', 'Q', 'K'
};

static const char _card_type[TEST_CARD_TYPE] = {
    'C', 'H', 'S', 'D'
};

static int get_card(void);

int main(void)
{
    time_t tSeed = 0;

    if ((tSeed = time(NULL)) == (time_t)-1) {
        fprintf(stderr, "time() error occurred by %s\n", strerror(errno));
        return 1;
    }
    srand((unsigned int)tSeed);

    for (size_t iCard = 0; iCard < TEST_CARD_NUM; iCard++) {
        int _card = get_card();

        if (_card < 0) {
            fprintf(stderr, "get_card failed\n");
            return 1;
        }
        printf("%zu Card: [%c]%c\n", iCard+1, _card_type[(_card/(TEST_CARD_NUM / TEST_CARD_TYPE))], _card_num[(_card % (TEST_CARD_NUM / TEST_CARD_TYPE))]);
    }

    return 0;
}

int get_card(void)
{
    int _card = -1;
    int ret = -1;
    
    if (_card_manager.rem_card <= 0) {
        return -1;
    }

    _card = rand() % _card_manager.rem_card;

    for (size_t iCard = 0; iCard < TEST_CARD_NUM; iCard++) {
        if (_card_manager.check[iCard] == 0) {
            if (_card == 0) {
                _card_manager.check[iCard] = 1;
                _card_manager.rem_card--;
                ret = iCard;
                break;
            }

            _card--;
        }
    }
    
    return ret;
}