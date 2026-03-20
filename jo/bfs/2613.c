#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { MAP_MAX = 1000, MAP_MARGIN = 2, MOVE_MAX = 4 };

/* M: Row, N: Column */
int M, N;
/* 
    Value
        - 1: 토마토가 있으며 익었음 -> 시작 가능한 지점을 의미
        - 0: 토마토가 있으며 아직 방문하지 않았음
        - 1 <: 토마토가 있으며 익었으며, 시작 가능한 지점은 아니지만, 익는데 걸린 시간
*/
int map[MAP_MAX + MAP_MARGIN][MAP_MAX + MAP_MARGIN];

typedef struct {
    int R;
    int C;
} stPOINT;

/* 일회용 큐 */
typedef struct {
    size_t front;
    size_t rear;

    stPOINT data[MAP_MAX * MAP_MAX];
} stQUEUE;

stQUEUE bfs_q;

stPOINT move_dir[MOVE_MAX] = {
    {1, 0},
    {-1, 0},
    {0, 1},
    {0, -1}
};

void stPOINT_Init(stQUEUE *q)
{
    q->front = 0;
    q->rear = 0;
}

void stPOINT_Enqueue(stQUEUE *q, stPOINT point)
{
    q->data[q->rear++] = point;
}

stPOINT *stPOINT_Dequeue(stQUEUE *q)
{
    if (q->front == q->rear) {
        return NULL;
    }

    return &q->data[q->front++];
}

void input(void)
{
    scanf("%d %d", &M, &N);

    for (int i = 0; i <= N+1; i++) {
        memset(map[i], -1, (sizeof(int) * (M + 2)));
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            int data;
            scanf(" %d", &data);
            map[i][j] = data;
            if (data == 1) {
                stPOINT_Enqueue(&bfs_q, (stPOINT){.R = i, .C = j});
            }
        }
    }
}

int bfs(stQUEUE *q)
{
    int _day_max = -1;

    stPOINT *cur_point;

    while (cur_point = stPOINT_Dequeue(q))
    {
        stPOINT cur = *cur_point;
        int _day = map[cur.R][cur.C];

        for (int i = 0; i < MOVE_MAX; i++) {
            stPOINT next_pos = {
                .R = cur.R + move_dir[i].R,
                .C = cur.C + move_dir[i].C
            };

            if (map[next_pos.R][next_pos.C] != 0)
                continue;

            map[next_pos.R][next_pos.C] = _day + 1;
            stPOINT_Enqueue(q, next_pos);
        }

        _day_max = ((_day > _day_max) ? _day : _day_max);
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (map[i][j] == 0) {
                return 0;
            }
        }
    }

    return _day_max;
}

int main(void)
{
    int day_max;

    // freopen("../../test.txt", "r", stdin);
    /* 입력을 받으며 동시에 1인 경우 start_point에 스타팅 포인트 선정 */

    input();

    day_max = bfs(&bfs_q);
    printf("%d", day_max - 1);

    return 0;
}
