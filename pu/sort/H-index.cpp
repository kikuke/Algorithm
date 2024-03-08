#include <algorithm>
#include <vector>

using namespace std;

int solution(vector<int> citations) {
  int rem_size, answer = 0;
  sort(citations.begin(), citations.end());

  for (int i = 0; i < citations.size(); i++) {
    rem_size = citations.size() - i;
    while (answer < citations[i] && answer < rem_size)
      answer++;
  }

  return answer;
}
