#include <stdio.h>
#include <stdbool.h>

enum { BELT_MAX = 30000, DIF_MAX = 3000 };

typedef struct {
    int dif_count;
    int dish[DIF_MAX];
} stEAT;

int N;  /* 초밥 접시 수 N */
int D;  /* 초밥 가짓 수 D */
int K;  /* 연속 먹는 점시 개수 K */
int C;  /* 쿠폰 번호 */
int belt[BELT_MAX];

stEAT eat;

int main(void)
{
    int _max = 0;

    scanf("%d %d %d %d", &N, &D, &K, &C);
    for (int i = 0; i < N; i++) {
        int sushi;
        scanf("%d", &sushi);
        belt[i] = sushi;
    }

    /* 초기 접시를 쌓아둠 */
    ++eat.dish[belt[N - 1]];
    ++eat.dif_count;
    for (int i = 0; i < (K - 1); i++) {
        if ((++eat.dish[belt[i]]) == 1) {
            eat.dif_count++;
        }
    }

    /* 미리 접시 쌓아놓고 이동하게되면 맨 마지막꺼 dish에서 하나 빼고 카운트 제어하는 방식 */
    for (int iBelt = 0; iBelt < N; iBelt++) {
        int iDel = ((iBelt - 1 + N) % N);           /* 지울 것 */
        int iAdd = ((iBelt + (K - 1) + N) % N);     /* 추가할 것 */
        int _temp = 0;

        if ((--eat.dish[belt[iDel]]) < 1) {
            --eat.dif_count;
        }
        if ((++eat.dish[belt[iAdd]]) == 1) {
            ++eat.dif_count;
        }

        _temp = eat.dif_count;
        if (eat.dish[C] == 0)
            _temp++;
        _max = (_max < _temp) ? _temp : _max;
    }

    printf("%d", _max);
    return 0;
}