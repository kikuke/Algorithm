#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { MAP_MAX = 100, MAP_MARGIN = 2, MAP_DIR_MAX = 4 };
enum { MAP_FILL_DATA = -1 };

typedef struct {
    int y;
    int x;
} stPOINT;

int stPOINT_IsEmpty(void);
int update_map(stPOINT cur_pos, stPOINT dir);

int N;

int map[MAP_MAX + MAP_MARGIN][MAP_MAX + MAP_MARGIN];
/* Fill MAP_FILL_DATA */
int map_w[MAP_MAX + MAP_MARGIN][MAP_MAX + MAP_MARGIN];

stPOINT move_dir[MAP_DIR_MAX] = {
    {1, 0},
    {-1, 0},
    {0, 1},
    {0, -1}
};

size_t q_front;
size_t q_rear;
stPOINT q[(MAP_MAX + MAP_MARGIN)*(MAP_MAX + MAP_MARGIN)*10];
stPOINT end_pos;

void init_data(void)
{
    scanf("%d", &N);

    /* Init Weight Map */
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            map_w[i][j] = MAP_FILL_DATA;
        }
    }
    
    scanf("%d %d", &end_pos.y, &end_pos.x);

    /* Init Height Map */
    for(int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            scanf("%d", &map[i][j]);
        }
    }
}

/* Return Value - 0: Success -1: Failed */
inline int update_map(stPOINT cur_pos, stPOINT dir)
{
    int weight = 0;
    stPOINT move_pos = {
        .y = (cur_pos.y + dir.y),
        .x = (cur_pos.x + dir.x)
    };

    /* Check Bound */
    if ((move_pos.x < 0) || (move_pos.y < 0) || (move_pos.x > N+1) || (move_pos.y > N+1))
        return -1;
    
    /* Out Line */
    if (map[move_pos.y][move_pos.x] == 0)
        return -1;
    
    /* Compare Height & Caculate Weight */
    {
        int gap = map[cur_pos.y][cur_pos.x] - map[move_pos.y][move_pos.x];
        if (gap > 0) {
            /* Case of Dec: dif */
            weight = gap;
        }
        else if (gap < 0) {
            /* Case of Asc: pow */
            weight = gap * gap;
        }
        else {
            /* Case Of Flat: 0 */
            weight = 0;
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

inline int stPOINT_IsEmpty(void) {
    return q_front == q_rear;
}

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

int main(void)
{
    // freopen("../../test.txt", "r", stdin);

    init_data();

    printf("%d\n", bfs());

    return 0;
}
