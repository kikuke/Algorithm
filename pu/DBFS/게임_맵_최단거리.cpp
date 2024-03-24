/* #include <vector> */
/* using namespace std; */
/**/
/* const int moveP[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}}; */
/**/
/* bool check[100][100]; */
/**/
/* int dfs(int x, int y, vector<vector<int>> maps) { */
/*   int best = -1; */
/**/
/*   check[y][x] = true; */
/*   if (x == maps[y].size() - 1 && y == maps.size() - 1) */
/*     return 1; */
/**/
/*   for (int i = 0; i < 4; i++) { */
/*     int nextY = y + moveP[i][1]; */
/*     int nextX = x + moveP[i][0]; */
/*     int tmp; */
/**/
/*     if (nextY < 0 || nextX < 0 || nextY >= maps.size() || */
/*         nextX >= maps[y].size()) */
/*       continue; */
/**/
/*     if (!check[nextY][nextX] && maps[nextY][nextX]) { */
/*       check[nextY][nextX] = true; */
/*       tmp = dfs(nextX, nextY, maps); */
/*       check[nextY][nextX] = false; */
/**/
/*       if (tmp > 0 && (best < 0 || best > tmp + 1)) { */
/*         best = tmp + 1; */
/*       } */
/*     } */
/*   } */
/**/
/*   return best; */
/* } */
/**/
/* int solution(vector<vector<int>> maps) { return dfs(0, 0, maps); } */

#include <queue>
#include <vector>
using namespace std;

typedef struct point {
  int x;
  int y;
  int depth;

  point operator+(point target) { return {x + target.x, y + target.y}; }
} point;

point next_move[] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

queue<point> q;
bool check[100][100];

int solution(vector<vector<int>> maps) {
  int answer = 0;

  q.push({0, 0, 1});
  while (!q.empty()) {
    point cur_p = q.front();
    q.pop();

    for (int i = 0; i < 4; i++) {
      point next_p = cur_p + next_move[i];
      next_p.depth = cur_p.depth + 1;

      // if (next_p.x < 0 || next_p.y < 0 || next_p.x >= maps[next_p.y].size()
      // || 와 같이 maps[next_p.y].size를 이용해 매 루프마다 각 행의 길이를
      // 구하면 오답처리 됩니다.
      if (next_p.x < 0 || next_p.y < 0 || next_p.x >= maps[0].size() ||
          next_p.y >= maps.size())
        continue;

      if (next_p.x == maps[next_p.y].size() - 1 && next_p.y == maps.size() - 1)
        return next_p.depth;

      if (maps[next_p.y][next_p.x] && !check[next_p.y][next_p.x]) {
        check[next_p.y][next_p.x] = true;
        q.push(next_p);
      }
    }
  }

  return -1;
}
