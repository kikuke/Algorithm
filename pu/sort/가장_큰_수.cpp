#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

using namespace std;

bool dict_cmp(string a, string b) { return a + b > b + a; }

string solution(vector<int> numbers) {
  string answer = "";

  vector<string> s_num;
  transform(numbers.begin(), numbers.end(), back_inserter(s_num),
            [](int n) { return to_string(n); });
  sort(s_num.begin(), s_num.end(), dict_cmp);

  for (string s : s_num)
    answer.append(s);

  for (char s : answer) {
    if (s != '0')
      return answer;
  }
  return "0";
}
