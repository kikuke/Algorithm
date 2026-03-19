#include <stdio.h>
#include <stdlib.h>

enum { VERTEX_MAX = 100000, VERTEX_OFF = 1, EDGE_MAX = 200000, BUFFER_MAX = 100000, VECTOR_CAP_INIT = 2 };

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

inline void stVECTOR_PushBack(int v1, int v2)
{
    if (connected[v1].cap == connected[v1].sz) {
        connected[v1].cap <<= 1;
        connected[v1].data = realloc(connected[v1].data, sizeof(int) * connected[v1].cap);
    }

    connected[v1].data[connected[v1].sz++] = v2;
}

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
    scanf("%d %d %d", &N, &M, &R);
    
    for (int i = 1; i <= N; i++) {
        connected[i].cap = VECTOR_CAP_INIT;
        connected[i].data = malloc(sizeof(int) * VECTOR_CAP_INIT);
    }
    
    for (int i=0; i<M; ++i) {
        int v1, v2;

        scanf("%d %d", &v1, &v2);

        stVECTOR_PushBack(v1, v2);
        stVECTOR_PushBack(v2, v1);
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
