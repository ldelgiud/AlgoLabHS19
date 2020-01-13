#include<iostream>
#include<vector>
using namespace std;

void test_case() {
  int n; cin >> n;

  vector<vector<int>> V(n+1, vector<int>(n+1));
  vector<vector<int>> V2(n+1, vector<int>(n+1,0));

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      cin >> V[i][j];
    }
  }

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      V2[i][j] = V2[i-1][j] + V2[i][j-1] - V2[i-1][j-1] + V[i][j];
    }
  }

  int even_pairs = 0;

  for (int i1 = 1; i1 <= n; ++i1) {
    for (int i2 = i1; i2 <= n; ++i2) {
      int even = 0, odd = 0, tmp = 0;

      for (int j = 1; j <= n; ++j) {
        int t = V2[i2][j] - V2[i2][j-1] - V2[i1-1][j] + V2[i1-1][j-1];
        tmp += t;
        if(tmp%2==0) ++even;
        else ++odd;
      }
      even_pairs += even * (even-1)/2 + odd * (odd-1)/2 + even;
    }
  }

  cout << even_pairs << endl;

}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; cin >> t;
  while(t--) test_case();
}
