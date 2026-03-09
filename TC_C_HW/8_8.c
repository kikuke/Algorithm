#include <stdio.h>
#include <stdlib.h>

enum { LEAF_MAX = 1000 };

int leaf_cnt;
int leaf[LEAF_MAX];

int comp(const void *a, const void *b)
{
    return *(int *)a > *(int *)b;
}

int get_count(int iStart, int iFirst)
{
    const int dist_min = leaf[iFirst] - leaf[iStart];
    const int dist_max = dist_min * 2;
    int _i_left, _i_mid, _i_right;
    int _i_min = 0, _i_max = 0;
    int res = 0;

    _i_left = iFirst + 1;
    _i_right = leaf_cnt;

    /* Get Lower */
    while (_i_left <= _i_right) {
        int dist_cur;

        _i_mid = (_i_left + _i_right) / 2;
        dist_cur = leaf[_i_mid] - leaf[iFirst];
        if ((dist_min <= dist_cur) && (dist_max >= dist_cur)) {
            _i_min = _i_mid;
            _i_right = _i_mid - 1;
        } else {
            _i_left = _i_mid + 1;
        }
    }

    
    _i_left = iFirst + 1;
    _i_right = leaf_cnt;

    /* Get Upper */
    while (_i_left <= _i_right) {
        int dist_cur;

        _i_mid = (_i_left + _i_right) / 2;
        dist_cur = leaf[_i_mid] - leaf[iFirst];
        if ((dist_min <= dist_cur) && (dist_max >= dist_cur)) { // 수정하기
            _i_max = _i_mid;
            _i_left = _i_mid + 1;
        } else {
            _i_right = _i_mid - 1;
        }
    }

    if (_i_min > 0) {
        res = (_i_max - _i_min) + 1;
    }

    return ((res > 0) ? res : 0);
}

int main(void)
{
    int iStart_max;
    int iFirst_max;
    int sum = 0;

    scanf("%d", &leaf_cnt);
    for (int iLeaf = 0; iLeaf < leaf_cnt; iLeaf++) {
        int input;
        scanf("%d", &input);
        leaf[iLeaf] = input;
    }
    /* Binary Search를 위한 정렬 */
    qsort(leaf, leaf_cnt, sizeof(*leaf), comp);

    iStart_max = leaf_cnt - 2;
    iFirst_max = leaf_cnt - 1;

    for (int iStart = 0; iStart < iStart_max; iStart++) {
        for (int iFirst = 1; iFirst < iFirst_max; iFirst++) {
            sum += get_count(iStart, iFirst);
        }
    }
    printf("%d", sum);

    return 0;
}