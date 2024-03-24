#include <vector>

using namespace std;

bool check[200];

// idx는 현재 탐색해야하는 노드
void dfs(int n, vector<vector<int>> computers, int idx) {
  for (int i = 0; i < n; i++) {
    if (!check[i] && computers[idx][i]) {
      check[i] = true;
      dfs(n, computers, i);
    }
  }

  return;
}

int solution(int n, vector<vector<int>> computers) {
  int answer = 0;

  for (int i = 0; i < n; i++) {
    if (!check[i]) {
      check[i] = true;
      answer++;
      dfs(n, computers, i);
    }
  }
  return answer;
}
