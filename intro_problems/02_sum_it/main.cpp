#include <iostream>

using namespace std;
int main() {
  int t;
  cin >> t;

  while (t--) {
    int sum = 0;
    int n;
    cin >> n;

    while (n--) {
      int temp;
      cin >> temp;
      sum += temp;
    }

    cout << sum << endl;
  }
}
