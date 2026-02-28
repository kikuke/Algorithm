#include <iostream>

using namespace std;

/**
 * @brief 개선 사항
 * 1. 행렬 정의 헷갈림
 * 2. 불필요한 출력 포맷
 */

constexpr size_t TEST_ARR_SIZE = 100 * 100;
int32_t test_arr[TEST_ARR_SIZE];
size_t test_n;
size_t test_m;

int main(void) {
    size_t arr_max = 0;

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> test_n >> test_m;
    arr_max = test_n * test_m;

    for (size_t i_arr = 0; i_arr < arr_max; i_arr++) {
        cin >> test_arr[i_arr];
    }
    for (size_t i_arr = 0; i_arr < arr_max; i_arr++) {
        int32_t test_data;

        cin >> test_data;
        test_arr[i_arr] += test_data;
    }

    for (size_t i_arr = 0; i_arr < arr_max; i_arr++) {
        cout << test_arr[i_arr];
        if (((i_arr + 1) % test_m) == 0) {
            cout << '\n';
        }
        else {
            cout << ' ';
        }
    }

    return 0;
}