#include <stdio.h>

enum { N_MAX = 1000, PHASE_MAX = 2 };

int jump[N_MAX];

void sort(int n)
{
    const int _i_max = n - 1;
    int _temp = 0;

    for (size_t i = 0; i < _i_max; i++) {
        const int _j_max = _i_max - i;

        for (size_t j = 0; j < _j_max; j++) {
            if (jump[j] > jump[j + 1]) {
                _temp = jump[j];
                jump[j] = jump[j+1];
                jump[j+1] = _temp;
            }
        }
    }
}

int main(void)
{
    int n = 0;
    int iPos_max;

    scanf("%d", &n);
    /* Binary Search를 하기 위한 정렬 */
    sort(n);

    /* Lower Bound, Upper Bound를 통해 구현 */
    iPos_max = n - 2;
    for (size_t iFrog = 0; iFrog < iPos_max; iFrog++) {
        int start_pos = jump[iFrog];

        for (size_t iPhase = 0; iPhase < PHASE_MAX; iPhase++) {
            
        }
    }
}