#include <iostream>

using namespace std;

/**
 * @brief Feedback
 * 합을 미리 계산해두기
 * 문제풀 때는 문제에만 집중
 */

constexpr size_t TEST_ARR_SIZE = 1000001UL;
static uint32_t arr_n[TEST_ARR_SIZE];
static uint32_t accNs[TEST_ARR_SIZE];

void getAccumulateSum(size_t n) {
    uint32_t sum = 0;

    for (uint32_t iN = 1; iN <= n; iN++) {
        sum += arr_n[iN];
        accNs[iN] = sum;
    }
}

int main(void)
{
    size_t n, m;

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    /* Get Array */
    for (size_t iN = 1; iN <= n; iN++) {
        cin >> arr_n[iN];
    }

    getAccumulateSum(n);

    /* Get Sum */
    for (size_t iM = 1; iM <= m; iM++) {
        size_t iI, iJ;
        uint32_t sum;

        cin >> iI >> iJ;
        sum = accNs[iJ] - accNs[iI - 1];
        cout << sum << "\n";
    }
}