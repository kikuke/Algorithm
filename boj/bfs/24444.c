#include <stdio.h>
#include <stdlib.h>

enum { VERTEX_MAX = 100000, EDGE_MAX = 200000, MARGIN = 1 };

typedef struct _stNODE {
    int vertex;

    struct _stNODE *next;
} stNODE;

typedef struct _stQ{
    size_t front;
    size_t rear;
    size_t cap;
    int data[EDGE_MAX + MARGIN];
} stQ;

/* 정점의 수 */
int N;
/* 간선의 수 */
int M;
/* 시작 정점 */
int R;
char visited[VERTEX_MAX + MARGIN];

stNODE vertex[VERTEX_MAX + MARGIN];

void stNode_Insert(stNODE *head, int vertex)
{
    stNODE *node = (stNODE *)malloc(sizeof(stNODE));
    node->vertex = vertex;
    node->next = NULL;

    for (stNODE *it = head; it != NULL; it = it->next) {
        if ((it->next == NULL) || it->next->vertex > node->vertex) {
            node->next = it->next;
            it->next = node;
            break;
        }
    }
    /* free는 프로그램 종료에게~ */
}

void stQ_Init(stQ *q)
{
    q->cap = EDGE_MAX;
    q->front = 0;
    q->rear = 0;
}

void stQ_Push(stQ *q, int vertex)
{
    /* Full */
    if ((q->rear > q->front) && (q->rear - q->front > q->cap))
        return;
    
    if ((q->rear < q->front) && (q->rear + 1 > q->front))
        return;
    
    q->data[q->rear++];
    if (q->rear > q->cap)
        q->rear = 0;
}

int stQ_Pop(stQ *q)
{
    int val;
    /* Emptry */
    if (q->front == q->rear)
        return;
    
    val = q->data[q->front++];
    if (q->front >= q->cap) {
        q->front = 0;
    }
    return val;
}

void bfs(void)
{
    stQ q;
    stQ_Init(&q);

    /* Init visited */
    visited[R] = 1;


}

void input(void)
{
    scanf("%d %d %d", &N, &M, &R);
    for (int i = 0; i < M; i++) {
        int v1, v2;
        scanf("%d %d", &v1, &v2);
        stNode_Insert(&vertex[v1], v2);
        stNode_Insert(&vertex[v2], v1);
    }
}

int main(void)
{
    input();
    bfs();

    return 0;
}
