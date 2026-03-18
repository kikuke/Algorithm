#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ENABLE_FREE     (0)

enum { STRING_MAX = 100000 };

typedef struct _stNode {
    char data;

    struct _stNode *prev;
    struct _stNode *next;
} stNode;

stNode *stNode_Input(stNode *cursor, stNode *input)
{
    stNode *prev = cursor->prev;
    
    input->prev = prev;
    cursor->prev = input;
    input->next = cursor;

    if (prev != NULL) {
        prev->next = input;
    }

    return cursor;
}

stNode *stNode_Create(char data) {
    stNode *node = NULL;

    node = (stNode *)malloc(sizeof(stNode));
    node->data = data;
    node->prev = NULL;
    node->next = NULL;

    return node;
}

stNode *stNode_Delete(stNode *cursor)
{
    stNode *prev = cursor->prev;
    stNode *next = cursor->next;

    if (prev->data == 0)
        return cursor;
    
    prev->prev->next = cursor;
    cursor->prev = prev->prev;
#if (ENABLE_FREE == 1)
    free(prev);
#endif

    return cursor;
}

int input(stNode *cursor)
{
    char str[STRING_MAX];
    char *iStr = str;
    char node_data;

    int cmd_line;

    scanf("%s", str);

    while ((node_data = *(iStr++))) {
        stNode_Input(cursor, stNode_Create(node_data));
    }
    scanf("%d", &cmd_line);

    return cmd_line;
}

void prompt(stNode **pCursor)
{
    char cmd;
    char data;
    scanf(" %c", &cmd);

    switch (cmd)
    {
    case 'L':
    {
        if ((*pCursor)->prev->data == 0) {
            break;
        }
        *pCursor = (*pCursor)->prev;
    }
    break;
    case 'D':
    {
        if ((*pCursor)->next == NULL) {
            break;
        }
        *pCursor = (*pCursor)->next;
    }
    break;
    case 'B':
    {
        stNode_Delete(*pCursor);
    }
    break;
    case 'P':
    {
        scanf(" %c", &data);
        stNode_Input(*pCursor, stNode_Create(data));
    }
    break;
    default:
        break;
    }
}

void output(stNode *node_home)
{
    for (stNode *it = node_home->next; it->next != NULL; it = it->next) {
        printf("%c", it->data);
    }
    printf("\n");
}

int main(void)
{
    stNode *node_home   = stNode_Create(0);
    stNode *node_eof    = stNode_Create(0);
    stNode *cursor = node_eof;
    int cmd_line;

    stNode_Input(cursor, node_home);

    cmd_line = input(cursor);

    for (int i = 0; i < cmd_line; i++) {
        prompt(&cursor);
    }

    output(node_home);
#if (ENABLE_FREE == 1)
    for (stNode *it = node_home->next; it != NULL; it = it->next) {
        free(it->prev);
    }
    free(node_eof);
#endif
    return 0;
}