#include <iostream>

/**
 * @brief Idea
 * string 자료형을 활용해보기, offset두고 반복하면 됨
 */

 /**
  * @brief Feedback
  * C++ 문법, STL에 익숙해질 필요
  */

using namespace std;

constexpr size_t TEST_STRING_MAX        = 1000UL;
constexpr size_t TEST_STRING_LEN_MAX    = 21;
static size_t test_max;

static size_t test_str_red[TEST_STRING_MAX];
static string test_str[TEST_STRING_MAX];

void print_red_string(size_t red, const string &str) {
    for (auto it: str) {
        for(size_t iRed = 0; iRed < red; iRed++) {
            cout << it;
        }
    }
    cout << '\n';
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> test_max;

    for (size_t iInput = 0; iInput < test_max; iInput++) {
        cin >> test_str_red[iInput] >> test_str[iInput];
    }

    for (size_t iInput = 0; iInput < test_max; iInput++) {
        print_red_string(test_str_red[iInput], test_str[iInput]);
    }

    return 0;
}
