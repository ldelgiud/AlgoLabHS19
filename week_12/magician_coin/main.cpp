#include <iostream>
#include <vector>
#include <iomanip>

#define trace(x) std::cout << #x << " = " << x <<std::endl
#define step(x) std::cout <<  "step: " << x <<std::endl

void test_case() {
  int n, k, m; std::cin >> n >> k >> m;

  std::vector<double> p;
  //p.push_back(0);
  for (int i = 0; i < n; ++i) {
    double p_i; std::cin >> p_i;
    p.push_back(p_i);    
  }

  std::vector< std::vector<double> > DP(n+1, std::vector<double>(m+1,0));
  DP[0][m] = 1;
  //for (int i = 0; i < m; ++i) DP[1][i] = p[n];
  for (int i = 0; i <= n; ++i) DP[i][m] = 1;

  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j < m; ++j) {
      double max = 0;

      for (int k = 0; k <= j; ++k) {
	if (j + k > m) continue;
	max = std::max(p[n-i]*DP[i-1][j+k] + (1-p[n-i])*DP[i-1][j-k], max);
	if (max == 1) break;
      }
      DP[i][j] = max;
    }
  }

  std::cout << DP[n][k] << std::endl;
}


int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout << std::fixed << std::setprecision(5);
  int t; std::cin >> t;
  while(t--) test_case();
}
