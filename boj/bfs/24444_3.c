#include <stdio.h>
#include <stdlib.h>

enum { VERTEX_MAX = 100000, VERTEX_OFF = 1, EDGE_MAX = 200000, BUFFER_MAX = 100000 };

typedef struct {
    int v1;
    int v2;
} stEDGE_PAIR;

typedef struct {
    size_t cap;
    size_t sz;
    int *data;
} stVECTOR;

typedef struct {
    size_t f;
    size_t r;
    int data[VERTEX_MAX + VERTEX_OFF];
} stQUEUE;

void stVECTOR_PushBack(int v1, int v2);
void stQUEUE_Push(int data);
int stQUEUE_Pop(void);
int stQUEUE_IsEmpty(void);

int visited[VERTEX_MAX + VERTEX_OFF];
stVECTOR connected[VERTEX_MAX + VERTEX_OFF];
stQUEUE q;
int N, M, R;

inline void stQUEUE_Push(int data)
{
    q.data[q.r++] = data;
}

inline int stQUEUE_Pop(void)
{
    return q.data[q.f++];
}

inline int stQUEUE_IsEmpty(void)
{
    return q.f == q.r;
}

int qsort_comp_asc(const void *v1, const void *v2)
{
    return (*(int*)v1 > *(int*)v2);
}

void input(void)
{
    stEDGE_PAIR *pair = NULL;

    scanf("%d %d %d", &N, &M, &R);

    pair = malloc(sizeof(stEDGE_PAIR) * M);

    for (int i=0; i<M; ++i) {
        stEDGE_PAIR *edge = pair + i;

        scanf("%d %d", &edge->v1, &edge->v2);
        connected[edge->v1].cap++;
        connected[edge->v2].cap++;
    }
    
    for (int i = 1; i <= N; i++) {
        if (connected[i].cap == 0)
            continue;
        connected[i].data = malloc(sizeof(int) * connected[i].cap);
    }

    for (int i=0; i<M; ++i) {
        stEDGE_PAIR *edge = pair + i;
        int v1 = edge->v1;
        int v2 = edge->v2;

        connected[v1].data[connected[v1].sz++] = v2;
        connected[v2].data[connected[v2].sz++] = v1;
    }

    for (int i = 1; i <= N; i++) {
        if (connected[i].sz == 0)
            continue;
        
        qsort(connected[i].data, connected[i].sz, sizeof(*connected[i].data), qsort_comp_asc);
    }
}

void bfs(void)
{
    int count = 0;
    visited[R] = ++count;
    stQUEUE_Push(R);

    while (!stQUEUE_IsEmpty())
    {
        int target = stQUEUE_Pop();
        size_t it_len = connected[target].sz;
        for (size_t i = 0; i < it_len; i++) {
            int next = connected[target].data[i];
            
            if (visited[next])  continue;;

            visited[next] = ++count;
            stQUEUE_Push(next);
        }
    }
}

int main(void)
{
    // freopen("../../test.txt", "r", stdin);
    input();
    
    bfs();

    for (int i = 1; i <= N; i++) {
        printf("%d\n", visited[i]);
    }

    return 0;
}
