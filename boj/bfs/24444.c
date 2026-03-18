#include <stdio.h>
#include <stdlib.h>

#define MAP_TYPE_NODE   (1)
#define MAP_TYPE_ARRAY  (2)
#define MAP_TYPE        (MAP_TYPE_ARRAY)

enum { VERTEX_MAX = 100000, EDGE_MAX = 200000, MARGIN = 1 };
enum { QUEUE_MAX = EDGE_MAX };

typedef struct _stQ{
    size_t front;
    size_t rear;
    size_t cap;
    int data[QUEUE_MAX];
} stQ;

/* 정점의 수 */
int N;
/* 간선의 수 */
int M;
/* 시작 정점 */
int R;
int visited[VERTEX_MAX + MARGIN];

#if (MAP_TYPE == MAP_TYPE_NODE)
typedef struct _stNODE {
    int vertex;

    struct _stNODE *next;
} stNODE;

stNODE node_head[VERTEX_MAX + MARGIN];

void stNode_Insert(stNODE *head, int vertex)
{
    stNODE *node = (stNODE *)malloc(sizeof(stNODE));
    node->vertex = vertex;
    node->next = NULL;

    for (stNODE *it = head; it != NULL; it = it->next) {
        stNODE *next = it->next;
        if ((next == NULL) || next->vertex > vertex) {
            node->next = next;
            it->next = node;
            break;
        }
    }
    /* free는 프로그램 종료에게~ */
}
#elif (MAP_TYPE == MAP_TYPE_ARRAY)

typedef struct {
    size_t sz;
    size_t fill;
    int *vertex;
} stARR_EDGE;

stARR_EDGE *arr_head[VERTEX_MAX + MARGIN];

typedef struct {
    int v1;
    int v2;
} stEDGE_PAIR;

void stARR_EDGE_Check(int v1, int v2)
{
    if (arr_head[v1] == NULL) {
        arr_head[v1] = (stARR_EDGE *)malloc(sizeof(stARR_EDGE));
        arr_head[v1]->sz = 0;
        arr_head[v1]->fill = 0;
    }
    if (arr_head[v2] == NULL) {
        arr_head[v2] = (stARR_EDGE *)malloc(sizeof(stARR_EDGE));
        arr_head[v2]->sz = 0;
        arr_head[v2]->fill = 0;
    }
    arr_head[v1]->sz++;
    arr_head[v2]->sz++;
}

int qsort_comp_asc(const void *v1, const void *v2)
{
    return (*(int*)v1 > *(int*)v2);
}

#endif

void stQ_Init(stQ *q)
{
    q->cap = QUEUE_MAX;
    q->front = 0;
    q->rear = 0;
}

void stQ_Push(stQ *q, int vertex)
{
    size_t next = ((q->rear + 1) % q->cap);

    /* Full */
    if (next == q->front)
        return;
    
    q->data[q->rear] = vertex;
    q->rear = next;
}

int stQ_Pop(stQ *q)
{
    int val;
    size_t next = ((q->front + 1) % q->cap);

    /* Empty */
    if (q->front == q->rear)
        return 0;
    
    val = q->data[q->front];
    q->front = next;
    return val;
}

void bfs(void)
{
    int visit_cnt = 0;
    stQ q;
    stQ_Init(&q);

    /* Init visited */
    visited[R] = ++visit_cnt;

    stQ_Push(&q, R);
    while (!(q.front == q.rear))
    {
        int v1 = stQ_Pop(&q);
#if (MAP_TYPE == MAP_TYPE_NODE)
        stNODE *node = node_head[v1].next;

        while(node != NULL) {
            int vertex = node->vertex;

            if (visited[vertex] == 0) {
                visited[vertex] = ++visit_cnt;
                stQ_Push(&q, vertex);
            }

            node = node->next;
        }
#elif (MAP_TYPE == MAP_TYPE_ARRAY)
        int v2_max = arr_head[v1]->sz;

        for (int iV2 = 0; iV2 < v2_max; iV2++) {
            int vertex = arr_head[v1]->vertex[iV2];

            if (visited[vertex] == 0) {
                visited[vertex] = ++visit_cnt;
                stQ_Push(&q, vertex);
            }
        }
#endif
    }
}

void input(void)
{
#if (MAP_TYPE == MAP_TYPE_ARRAY)
    /* 임시 입력 공간 생성 */
    stEDGE_PAIR *pair_input;
    pair_input = (stEDGE_PAIR *)malloc(sizeof(stEDGE_PAIR) * EDGE_MAX);

#endif
    scanf("%d %d %d", &N, &M, &R);
    for (int i = 0; i < M; i++) {
        int v1, v2;
        scanf("%d %d", &v1, &v2);
#if (MAP_TYPE == MAP_TYPE_NODE)
        stNode_Insert(&node_head[v1], v2);
        stNode_Insert(&node_head[v2], v1);
#elif (MAP_TYPE == MAP_TYPE_ARRAY)
        /* 임시 입력 값 저장 */
        pair_input[i] = (stEDGE_PAIR){ v1, v2 };

        /* vertex edge 개수 체크 */
        stARR_EDGE_Check(v1, v2);
#endif
    }
#if (MAP_TYPE == MAP_TYPE_ARRAY)
    /* vertex edge 개수에 맞는 배열 생성 */
    for (int i = 1; i <= N; i++) {
        if (arr_head[i] == NULL)
            continue;
        arr_head[i]->vertex = (int *)malloc(arr_head[i]->sz * sizeof(int));
    }

    /* input 값 입력 */
    for (int i = 0; i < M; i++) {
        int v1 = pair_input[i].v1;
        int v2 = pair_input[i].v2;

        arr_head[v1]->vertex[arr_head[v1]->fill++] = v2;
        arr_head[v2]->vertex[arr_head[v2]->fill++] = v1;
    }

    /* 정렬 */
    for (int i = 1; i <= N; i++) {
        if (arr_head[i] == NULL)
            continue;
        
        qsort(arr_head[i]->vertex,
            arr_head[i]->sz, 
            sizeof(*arr_head[i]->vertex),
            qsort_comp_asc);
    }
    /* 임시 입력 공간 해제 */
    free(pair_input);
#endif
}

int main(void)
{
    input();
    
    bfs();

    for (int i = 1; i <= N; i++) {
        printf("%d\n", visited[i]);
    }

    return 0;
}
