#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

constexpr size_t ALPHABET_MAX = 'z' - 'a' + 1;

int main(void) {
    string word;
    vector<int32_t> arphabet_pos(ALPHABET_MAX);

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    fill(arphabet_pos.begin(), arphabet_pos.end(), -1);
    cin >> word;

    for (size_t i_word = 0; i_word < word.size(); i_word++) {
        size_t idx = static_cast<size_t>(word[i_word] - 'a');

        if (arphabet_pos[idx] == -1) {
            arphabet_pos[idx] = i_word;
        }
    }

    for (int32_t idx: arphabet_pos) {
        cout << idx << ' ';
    }

    return 0;
}