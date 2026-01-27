#include <iostream>

using namespace std;

constexpr size_t arr_max = 9 * 9;
static int32_t n_max = 0;
static size_t i_n_max = 0;

int main(void) {
    size_t i_n, i_m;
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (size_t i_arr = 0; i_arr < arr_max; i_arr++) {
        int32_t temp_n;

        cin >> temp_n;
        if (temp_n > n_max) {
            n_max = temp_n;
            i_n_max = i_arr;
        }
    }
    i_n = (i_n_max / 9) + 1;
    i_m = (i_n_max % 9) + 1;
    
    cout << n_max << '\n' << i_n << ' ' << i_m << '\n';

    return 0;
}