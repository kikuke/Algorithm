#include <algorithm>
#include <vector>

using namespace std;

vector<int> solution(vector<int> array, vector<vector<int>> commands) {
  vector<int> answer;

  for (vector<int> cmd : commands) {
    vector<int> tmp_arr;

    for (int i = cmd[0] - 1; i < cmd[1]; i++)
      tmp_arr.push_back(array[i]);

    sort(tmp_arr.begin(), tmp_arr.end());
    answer.push_back(tmp_arr[cmd[2] - 1]);
  }
  return answer;
}
