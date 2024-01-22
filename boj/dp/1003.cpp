#include <iostream>

using namespace std;

int n;
int arr[41][2] = {1, 0, 0, 1, 1, 1};
int arrCol = sizeof(arr) / sizeof(*arr);

void printArr(int idx) { cout << arr[idx][0] << " " << arr[idx][1] << endl; }

void cal_fibo() {
  for (int i = 3; i < arrCol; i++) {
    arr[i][0] = arr[i - 1][0] + arr[i - 2][0];
    arr[i][1] = arr[i - 1][1] + arr[i - 2][1];
  }
}

int main(void) {
  cin >> n;

  cal_fibo();
  for (int i = 0; i < n; i++) {
    int idx;
    cin >> idx;

    printArr(idx);
  }
  return 0;
}
