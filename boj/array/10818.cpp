#include <iostream>

using namespace std;

/**
 * @brief Idea
 * 정렬이 아니므로 순차탐색하면서 최대, 최소를 비교
 */

/**
 * @brief Feedback
 * 개발 환경 설정하는데 시간 걸림
 */

constexpr int32_t TEST_INT_MIN = -1000000;  /* 매크로보다 타입 추적용이 */
constexpr int32_t TEST_INT_MAX = 1000000;

constexpr size_t ARR_INT_SIZE = 1000000;

int32_t arr_int[ARR_INT_SIZE];  /* Vector 자료구조 사용 고려 */
size_t n;

int main(void)
{
    ios::sync_with_stdio(false);    /* 표준 입출력간 동기화 Disable */
    cin.tie(nullptr);               /* 수동 cout.flush() */

    int32_t _int_min = TEST_INT_MAX, _int_max = TEST_INT_MIN;

    cin >> n;

    for (size_t iArr = 0; iArr < n; iArr++) {
        cin >> arr_int[iArr];
    }

    for (size_t iArr = 0; iArr < n; iArr++) {
        int32_t _test_int;

        _test_int = arr_int[iArr];
        _int_min = ((_int_min < _test_int) ? _int_min : _test_int);
        _int_max = ((_int_max > _test_int) ? _int_max : _test_int);
    }

    cout << _int_min << " " << _int_max << '\n';

    return 0;
}
