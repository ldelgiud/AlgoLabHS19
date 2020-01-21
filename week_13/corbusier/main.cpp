#include <iostream>
#include <vector>

void test_case() {
  int n, rest, k; std::cin >> n >> rest >> k;
  std::vector<int> height;
  height.reserve(n);
  
  for (int j = 0; j < n; ++j) {
    int h; std::cin >> h;
    height.push_back(h%k);
  }
  
  std::vector<std::vector<bool>> DP(n,std::vector<bool>(k,false));
  DP[0][height[0]] = true;

  for (int j = 1; j < n; ++j) {
    for (int r = 0; r < k; ++r) {
      if (r < height[j]) {
	DP[j][r] = DP[j-1][r] || DP[j-1][k+(r-height[j])];
      } else if (r == height[j]) {
	DP[j][r] = true;
      }
      else {
	DP[j][r] = DP[j-1][r] || DP[j-1][r-height[j]];
      }
    }
  }
  
  if (DP[n-1][rest]) std::cout << "yes\n";
  else std::cout << "no\n";
} 

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) test_case();
}
