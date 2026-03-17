#include <stdio.h>

enum { MAP_MAX = 13, MAP_MARGIN = 1 };
int map_max;
int map[MAP_MAX + MAP_MARGIN][MAP_MAX + MAP_MARGIN];

int check[MAP_MAX + MAP_MARGIN];
int _min = 100 * 13;

int search(int depth, int start, int total)
{
    int _total = total;

    if (depth >= map_max) {
        if (map[start][0] != 0)
            return total + map[start][0];
        return 0;
    }

    for (int i = 1; i < map_max; i++) {
        if ((check[i] != 0) || (map[start][i] == 0))
            continue;
        _total = total + map[start][i];
        if (_total >= _min)
            continue;
        
        check[i] = 1;
        _total = search(depth + 1, i, _total);
        if ((_total > 0) && (_total < _min)) { 
            _min = _total;
        }
        check[i] = 0;
    }

    return _min;
}

void input(void)
{
    int weight;

    scanf("%d", &map_max);
    for (int i = 0; i < map_max; ++i) {
        for (int j = 0; j < map_max; ++j) {
            scanf("%d", &weight);
            map[i][j] = weight;
        }
    }
}

int main(void)
{
    int start = 0;
    int min_val = 100;
    input();

    check[0] = 1;
    printf("%d\n", search(1, 0, 0));

    return 0;
}
