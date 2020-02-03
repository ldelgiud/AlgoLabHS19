#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>

#define trace(x) std::cerr << #x << " = " << x<< std::endl
void test_case() {
  int n, k, x_; std::cin >> n >> k >> x_;
  std::bitset<16> x(x_);
  std::vector<std::bitset<16>> lights;
  for (int i = 0; i < n/k; ++i) {
    std::bitset<16> pattern(0);
    for (int j = 1; j <= k; ++j) {
      bool b; std::cin >> b;
      pattern[k-j] = b;
    }
    lights.push_back(pattern);
  }

  std::vector<int> cost;
  cost.push_back(0);
  for (int i = 0; i < n/k; ++i) {
    int tmp = (lights[i] ^= x).count();
    cost.push_back(tmp);
    //trace(tmp);
  }

  std::vector<std::pair<int,int>> DP(n/k+1, {0,0});

  for (int i = 1; i <= n/k; ++i) {
    DP[i].first =  std::min(cost[i] + DP[i-1].first, 1+k-cost[i]+DP[i-1].second);
    DP[i].second = std::min(k-cost[i] + DP[i-1].second, 1+cost[i]+DP[i-1].first);
  }

  std::cout << DP[n/k].first << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) test_case();

}
