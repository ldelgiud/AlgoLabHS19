#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

void test_case() {
  int n; cin >> n;

  vector<int> V;
  V.reserve(n);
  
  for (int i = 0; i < n; ++i) {
    int tmp; cin >> tmp;
    V.push_back(tmp);
  }

  int x; cin >> x;
  if (x) {
    std::sort(V.begin(), V.end(), greater<int>());
  } else {
    sort(V.begin(), V.end());
  }

  for (int i : V) {
    cout << i << ' ';
  }

  cout << endl;
}

int main() {
  int t; cin >> t;
  while(t--) test_case();

}
