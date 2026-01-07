#include <iostream>

using namespace std;

/**
 * @brief Idea
 * 순차탐색하며 최댓값 offset을 보관
 */

 /**
  * @brief Feedback
  * cin은 타입에 따라 자동으로 버퍼에서 꺼내씀
  * cin >> uint8_t하면 char처럼 취급
  */

constexpr size_t TEST_ARR_SIZE = 9;
static uint32_t arr_n[TEST_ARR_SIZE];

int main(void)
{
    size_t _max_idx = 0;

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (size_t iArr = 0; iArr < TEST_ARR_SIZE; iArr++) {
        cin >> arr_n[iArr];
    }

    for (size_t iArr = 0; iArr < TEST_ARR_SIZE; iArr++) {
        if (arr_n[_max_idx] < arr_n[iArr]) {
            _max_idx = iArr;
        }
    }

    cout << arr_n[_max_idx] << '\n' << _max_idx + 1 << '\n';

    return 0;
}