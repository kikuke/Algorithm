#include <stdio.h>

enum { MAP_MAX = 100, MAP_MARGIN = 2, MOVE_DIR_MAX = 4 };

typedef struct {
    int R;
    int C;
    int T;
} stNODE;

void Enqueue(stNODE data);
stNODE *Dequeue(void);

stNODE queue[MAP_MAX * MAP_MAX];
int front, rear;

char map[MAP_MAX + MAP_MARGIN][MAP_MAX + MAP_MARGIN];
int R, C;
int sR, sC; // 시작 행렬
int cnt;    // 남은 저글링

stNODE move_dir[MOVE_DIR_MAX] = {
    { 1,  0},
    {-1,  0},
    { 0,  1},
    { 0, -1}
};

inline void Enqueue(stNODE data)
{
    queue[rear++] = data;
}

inline stNODE *Dequeue(void)
{
    if (rear == front)
        return NULL;
    return &queue[front++];
}

void input(void)
{
    scanf("%d %d", &C, &R);
    for (int i = 1; i <= R; ++i) {
        scanf("%s", map[i] + 1);
        for (int j = 1; j <= C; ++j) {
            map[i][j] -= '0';
            cnt += map[i][j];
        }
    }

    scanf("%d %d", &sC, &sR);
}

int bfs(int sR, int sC)
{
    int time = 0;
    stNODE *cur = NULL;

    front = rear = 0;
    Enqueue((stNODE){sR, sC, 3});
    map[sR][sC] = 0;

    while (cur = Dequeue())
    {
        stNODE _cur = *cur;

        time = _cur.T;
        for (int i=0; i < MOVE_DIR_MAX; ++i) {
            stNODE move = (stNODE){_cur.R + move_dir[i].R, _cur.C + move_dir[i].C, _cur.T + 1};
            if (map[move.R][move.C] == 0)
                continue;
            map[move.R][move.C] = 0;
            Enqueue(move);
        }
    }

    return time;
}

int main(void)
{
    int result;
    // freopen("../../test.txt", "r",stdin);
    input();
    result = bfs(sR, sC);
    printf("%d\n%d\n" , result, cnt - rear);

    return 0;
}
