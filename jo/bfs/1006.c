#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { MAP_MAX = 100, MAP_MARGIN = 2 };
enum { MAP_FILL_DATA = -1 };

typedef enum {
    eOP_TURN_L = 0,
    eOP_TURN_R,
    eOP_GO_1,
    eOP_GO_2,
    eOP_GO_3,
    eOP_GO_MAX,
} eOP;

typedef enum {
    eDIR_DUMMY = 0,
    eDIR_R,
    eDIR_L,
    eDIR_D,
    eDIR_U,
    eDIR_MAX
} eDIR;

enum { STAT_QUEUE_MAX = ((eDIR_MAX)*(MAP_MAX + MAP_MARGIN)*(MAP_MAX + MAP_MARGIN) + 1) };

typedef struct {
    int y;
    int x;
} stPOINT;

typedef struct {
    stPOINT pos;
    eDIR    dir;
} stSTAT;

typedef struct {
    size_t front;
    size_t rear;
    stSTAT data[STAT_QUEUE_MAX];
} stSTAT_QUEUE;

/* Return
    Success: 0
    Fail: -1
*/
int stSTAT_QUEUE_Push(stSTAT *stat);
/* Need to Deep Copy, Null Value: Empty */
stSTAT *stSTAT_QUEUE_Pop(void);

stSTAT stSTAT_Operate(stSTAT cur_stat, eOP op);

/* Return
    Success: 0
    Fail: -1
*/
int update_map(stSTAT cur_stat, eOP op);

stPOINT move_dir[eDIR_MAX] = {
    [eDIR_DUMMY] = {0, 0}, /* Dummy */
    [eDIR_R] = {+0, +1},
    [eDIR_L] = {+0, -1},
    [eDIR_D] = {-1, +0},
    [eDIR_U] = {+1, +0}
};

stSTAT stat_start;
stSTAT stat_end;
stSTAT_QUEUE q;

/* M: R, N: C */
int M, N;

int map[MAP_MAX + MAP_MARGIN][MAP_MAX + MAP_MARGIN];
/* 바라보고있는 방향 시점의 가중치 맵 */
int map_w[eDIR_MAX][MAP_MAX + MAP_MARGIN][MAP_MAX + MAP_MARGIN];

void init_data(void)
{
    scanf("%d %d", &M, &N);

    /* Init Weight Map */
    for (int i = 1; i < eDIR_MAX; ++i) {
        for (int j = 1; j <= M; ++j) {
            for (int k = 1; k <= N; ++k) {
                map_w[i][j][k] = MAP_FILL_DATA;
            }
        }
    }

    /* Init Map */
    memset(map[0], 0xFF, sizeof(int) * (N+2));
    for(int i = 1; i <= N; ++i) {
        map[i][0] = 0xFFFFFFFF;
        for (int j = 1; j <= N; ++j) {
            scanf("%d", &map[i][j]);
        }
        map[i][N+1] = 0xFFFFFFFF;
    }
    memset(map[M+1], 0xFF, sizeof(int) * (N+2));
    
    scanf("%d %d %d", &stat_start.pos.y, &stat_start.pos.x, &stat_start.dir);
    scanf("%d %d %d", &stat_end.pos.y, &stat_end.pos.x, &stat_end.dir);
}

inline int stSTAT_QUEUE_Push(stSTAT *stat)
{
    size_t next_rear = (q.rear + 1) % STAT_QUEUE_MAX;

    if (next_rear == q.front)
        return -1;

    q.data[q.rear] = *stat;
    q.rear = next_rear;
    return 0;
}

inline stSTAT *stSTAT_QUEUE_Pop(void)
{
    size_t next_front = (q.front + 1) % STAT_QUEUE_MAX;
    stSTAT *stat = NULL;

    /* Check Empty */
    if (q.front == q.rear)
        return NULL;
    
    stat = &q.data[q.front];
    q.front = next_front;

    return stat;
}

inline stSTAT stSTAT_Operate(stSTAT cur_stat, eOP op)
{
    stSTAT next_stat = cur_stat;

    switch (op)
    {
    case eOP_TURN_L:
    {
        switch (next_stat.dir)
        {
        case eDIR_R:
            next_stat.dir = eDIR_U;
            break;
        case eDIR_L:
            next_stat.dir = eDIR_D;
            break;
        case eDIR_D:
            next_stat.dir = eDIR_R;
            break;
        case eDIR_U:
            next_stat.dir = eDIR_L;
            break;
        default:
            break;
        }
    }
    break;
    case eOP_TURN_R:
    {
        switch (next_stat.dir)
        {
        case eDIR_R:
            next_stat.dir = eDIR_D;
            break;
        case eDIR_L:
            next_stat.dir = eDIR_U;
            break;
        case eDIR_D:
            next_stat.dir = eDIR_L;
            break;
        case eDIR_U:
            next_stat.dir = eDIR_R;
            break;
        default:
            break;
        }
    }
    break;
    case eOP_GO_1:
        next_stat.pos = (stPOINT){
            .y = cur_stat.pos.y + (move_dir[cur_stat.dir].y * 1),
            .x = cur_stat.pos.x + (move_dir[cur_stat.dir].x * 1)
        };
        break;
    case eOP_GO_2:
        next_stat.pos = (stPOINT){
            .y = cur_stat.pos.y + (move_dir[cur_stat.dir].y * 2),
            .x = cur_stat.pos.x + (move_dir[cur_stat.dir].x * 2)
        };
        break;
    case eOP_GO_3:
        next_stat.pos = (stPOINT){
            .y = cur_stat.pos.y + (move_dir[cur_stat.dir].y * 3),
            .x = cur_stat.pos.x + (move_dir[cur_stat.dir].x * 3)
        };
        break;
    
    default:
        break;
    }

    return next_stat;
}

inline int update_map(stSTAT cur_stat, eOP op)
{
    int weight = 0;
    stSTAT next_stat = stSTAT_Operate(cur_stat, op);
    
    /* Out Line */
    if (map[move_pos.y][move_pos.x] == 0)
        return -1;
    
    /* Compare Height & Caculate Weight */
    {
        int gap = map[cur_pos.y][cur_pos.x] - map[move_pos.y][move_pos.x];
        weight = gap;
        if (gap < 0) {
            /* Case of Asc: pow */
            weight *= gap;
        }
        weight += map_w[cur_pos.y][cur_pos.x];
    }

    /* Check If Update & Update */
    if ((map_w[move_pos.y][move_pos.x] != MAP_FILL_DATA) && (map_w[move_pos.y][move_pos.x] <= weight)) {
        return -1;
    }

    map_w[move_pos.y][move_pos.x] = weight;
    return 0;
}
#if 0

int bfs(void)
{
    const int N_BOUND = N + 1;

    /* init Q */
    for (int i = 1; i <= N; ++i) {
        q[q_rear++] = (stPOINT) { .y = 0, .x = i };
        q[q_rear++] = (stPOINT) { .y = N_BOUND, .x = i };
        q[q_rear++] = (stPOINT) { .y = i, .x = 0 };
        q[q_rear++] = (stPOINT) { .y = i, .x = N_BOUND };
    }

    while (!stPOINT_IsEmpty()) {
        stPOINT cur_pos = q[q_front++];
        for (size_t i_dir = 0; i_dir < MAP_DIR_MAX; i_dir++){
            if (update_map(cur_pos, move_dir[i_dir]) < 0)
                continue;

            q[q_rear++] = (stPOINT) {
                .y = (cur_pos.y + move_dir[i_dir].y),
                .x = (cur_pos.x + move_dir[i_dir].x)
            };
        }
    }

    return map_w[end_pos.y][end_pos.x];
}
#endif

int main(void)
{
    freopen("../../test.txt", "r", stdin);

    init_data();

    // printf("%d\n", bfs());

    return 0;
}
