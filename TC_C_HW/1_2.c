#include <stdio.h>
#include <errno.h>
#include <string.h>

typedef enum {
    ePRINT_RESULT_SUCCESS = 0,
    ePRINT_RESULT_FAIL,
    ePRINT_RESULT_MAX
} ePRINT_RESULT;

enum { TEST_TRY_MAX = 3 };

static const char *print_result[ePRINT_RESULT_MAX] = {
    [ePRINT_RESULT_SUCCESS] = "로그인 성공!",
    [ePRINT_RESULT_FAIL]    = "관리자에게 문의하세요."
};

static const int test_value = 1357;

int main(void)
{
    int input = -1;
    ePRINT_RESULT res = ePRINT_RESULT_FAIL;

    for (size_t iTry = 0; iTry < TEST_TRY_MAX; iTry++) {
        if (scanf("%d", &input) != 1) {
            fprintf(stderr, "Error was occured by %s.", strerror(errno));
        }
        
        if (input == test_value) {
            res = ePRINT_RESULT_SUCCESS;
            break;
        }
    }

    printf("%s\n", print_result[res]);

    return 0;
}