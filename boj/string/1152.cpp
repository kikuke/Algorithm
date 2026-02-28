#include <iostream>

using namespace std;

/**
 * @brief Idea
 * 라인 전체 받아서 공백만 세기. 앞 뒤 공백 유의
 */

 /**
  * @brief Feedback
  * 공백 전체 받는 함수, 문제 꼼꼼히 읽기 
  */

static string test_str;

int main(void)
{
    size_t sp_cnt = 0;

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    getline(cin, test_str);
    for(size_t iStr = 0; iStr < test_str.length(); iStr++) {
        if ((test_str[iStr] != ' ') && ((test_str[iStr + 1] == ' ') || ((iStr + 1) == test_str.length()))) {
            sp_cnt++;
        }
    }

    cout << sp_cnt << '\n';

    return 0;
}
