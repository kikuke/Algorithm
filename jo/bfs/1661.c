#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { MAP_MAX = 1000, MAP_MARGIN = 2, MOVE_MAX = 4 };

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

void stPOINT_Init(stQUEUE *q);
void stPOINT_Enqueue(stQUEUE *q, stPOINT point);
stPOINT *stPOINT_Dequeue(stQUEUE *q);


stPOINT move_dir[MOVE_MAX] = {
    {1, 0},
    {-1, 0},
    {0, 1},
    {0, -1}
};

stQUEUE bfs_q;

/* M: Row, N: Column */
int M, N;
int map[MAP_MAX + MAP_MARGIN][MAP_MAX + MAP_MARGIN];

stPOINT start_pos;
stPOINT end_pos;

inline void stPOINT_Init(stQUEUE *q)
{
    q->front = 0;
    q->rear = 0;
}

inline void stPOINT_Enqueue(stQUEUE *q, stPOINT point)
{
    q->data[q->rear++] = point;
}

inline stPOINT *stPOINT_Dequeue(stQUEUE *q)
{
    if (q->front == q->rear) {
        return NULL;
    }

    return &q->data[q->front++];
}

void input(void)
{
    char c_map[MAP_MAX + MAP_MARGIN];

    scanf("%d %d", &N, &M);
    scanf("%d %d %d %d", &start_pos.C, &start_pos.R, &end_pos.C, &end_pos.R);

    memset(map[0], 0xFF, sizeof(int) * (N+2));
    for (int i = 1; i <= M; i++) {
        scanf("%s", c_map + 1);

        map[i][0] = 0xFFFFFFFF;
        for (int j = 1; j <= N; j++) {
            map[i][j] = (int)c_map[j] - '0';
        }
        map[i][N+1] = 0xFFFFFFFF;
    }
    memset(map[M+1], 0xFF, sizeof(int) * (N+2));
}

int bfs(stQUEUE *q)
{
    stPOINT *cur_point;
    stPOINT_Enqueue(q, start_pos);
    map[start_pos.R][start_pos.C] = 1;

    while (cur_point = stPOINT_Dequeue(q))
    {
        stPOINT cur = *cur_point;
        int _day = map[cur.R][cur.C];

        for (int i = 0; i < MOVE_MAX; ++i) {
            stPOINT next_pos = {
                .R = cur.R + move_dir[i].R,
                .C = cur.C + move_dir[i].C
            };

            if (map[next_pos.R][next_pos.C] != 0)
                continue;

            map[next_pos.R][next_pos.C] = _day + 1;

            if ((next_pos.R == end_pos.R) && (next_pos.C == end_pos.C)) {
                return map[next_pos.R][next_pos.C];
            }
            stPOINT_Enqueue(q, next_pos);
        }
    }

    return 0;
}

int main(void)
{
    int day_max;

    // freopen("../../test.txt", "r", stdin);

    input();

    day_max = bfs(&bfs_q);
    printf("%d", day_max - 1);

    return 0;
}
