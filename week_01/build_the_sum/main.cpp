#include<iostream>

using namespace std;

void test_case() {
  int n; cin >> n;
  int sum = 0;
  for (int i = 0; i < n; ++i) {
    int tmp; cin >> tmp;
    sum += tmp;
  }

  cout << sum << endl;
  
}

int main() {
  int t; cin >> t;
  while(t--) test_case();
}
