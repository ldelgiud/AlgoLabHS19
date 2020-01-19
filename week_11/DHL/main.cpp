#include <iostream>
#include <vector>
#include <deque>

int n;
std::vector<std::vector<int>> DP;
std::vector<int> A, B;

int cost(int i, int j, int l, int r) {
  int sum_l = 0, sum_r = 0;
  for (int  u = i-1; u >= i-l; --u) {
    sum_l += A[u];
  }

  for (int u = j-1; u >= j-r; --u) {
    sum_r += B[u];
  }
  return (sum_l-l)*(sum_r-r);
}

int play(int i, int j) {

  if (DP[i][j] != -1) return DP[i][j];
  int min = 1 << 27;
  for (int l = 1; l <= i; ++l) {
    for (int r = 1; r <= j; ++r) {
      int new_i = i-l;
      int new_j = j-r;
      if (new_i < 0 || new_j < 0) continue;
      if (new_i == 0 && new_j == 0) min = std::min(min, cost(i,j,l,r));
      else {
	min = std::min(min, play(new_i, new_j) + cost(i,j,l,r));
      }					   
    }
  }
  DP[i][j] = min;
  return min;
}
void test_case() {

  std::cin >> n;
  A.clear(); B.clear();
  for (int i = 0; i < n; ++i) {
    int a; std::cin >> a;
    A.push_back(a);
  }

  for (int i = 0; i < n; ++i) {
    int b; std::cin >> b;
    B.push_back(b);
  }

  DP.clear();
  DP = std::vector<std::vector<int>>(n+1, std::vector<int>(n+1, -1));
  for (int i = 1; i < n; ++i) {
    DP[i][0] = 1 << 27;
    DP[0][i] = 1 << 27;
  }
  DP[0][0] = 0;
  int total = play(n,n);
  std::cout << total << std::endl;
}



int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) test_case();

}
