#include <numeric>
#include <vector>

using namespace std;

int dfs(vector<int> numbers, int target, int idx) {
  int sum = 0;
  if (idx == numbers.size())
    return target == accumulate(numbers.begin(), numbers.end(), 0);

  sum += dfs(numbers, target, idx + 1);
  numbers[idx] = ~numbers[idx] + 1;
  sum += dfs(numbers, target, idx + 1);
  return sum;
}

int solution(vector<int> numbers, int target) {
  int answer = dfs(numbers, target, 0);

  return answer;
}
