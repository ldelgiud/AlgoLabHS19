#include <iostream>
#include <vector>
#include <deque>

void test_case() {

  int n; std::cin >> n;
  std::vector<int> A, B;
  A.push_back(0);
  B.push_back(0);
  for (int i = 0; i < n; ++i) {
    int a; std::cin >> a;
    A.push_back(a-1);
  }
  for (int i = 0; i < n; ++i) {
    int b; std::cin >> b;
    B.push_back(b-1);
  }

  std::vector< std::vector<int> > DP(n+1, std::vector<int>(n+1,0));
  std::vector<long> preA(n+1,0), preB(n+1,0);

  for (int i = 1; i <= n; ++i) {
    preA[i] = preA[i-1] + A[i];
    preB[i] = preB[i-1] + B[i];
  }
  
  for (int i = 1; i <= n; ++i) {
    DP[1][i] = A[1] * preB[i];
    DP[i][1] = B[1] * preA[i];
  }

  for (int i = 2; i <= n; ++i) {
    for (int j = 2; j <= n; ++j) {
      DP[i][j] = A[i]*B[j] + std::min(DP[i-1][j-1],
				      std::min(DP[i][j-1],
					       DP[i-1][j]));

    }
  }

  std::cout << DP[n][n] << std::endl;;
}



int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) test_case();

}
