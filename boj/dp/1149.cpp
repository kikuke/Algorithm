#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

int n;
int bef[3];
int now[3];
int result;

int main(void) {
  cin >> n;
  for (int i = 0; i < n; i++) {
    scanf("%d %d %d", &now[0], &now[1], &now[2]);
    for (int j = 0; j < 3; j++) {
      now[j] += min(bef[(j - 1 + 3) % 3], bef[(j + 1 + 3) % 3]);
    }
    memcpy(bef, now, sizeof(int) * 3);
  }
  result = min(now[0], min(now[1], now[2]));

  cout << result << endl;
  return 0;
}
