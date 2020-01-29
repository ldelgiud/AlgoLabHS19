#include <iostream>
#include <vector>
#include <queue>


#define trace(x) std::cout << #x << " = " << x << std::endl
#define traceVec(x) std::cout << #x << ": "; for (auto i : x) std::cout << i << ", "; std::cout << std::endl;
void test_case() {
  int n, m, k; std::cin >> n >> m >> k;

  std::vector<int> line;
  line.reserve(n+1);
  line.push_back(0);
  for (int i = 0; i < n; ++i) {
    int v; std::cin >> v;
    line.push_back(v);
  }

  
  int partial = line[1], counter = 0;
  std::vector<int> begin(n+1,-1);
  int l = 1, r = 1;
  while(true) {
    
    if (partial < k) {
      if (r < n) {
	partial += line[++r];
      } else break;
    } else if (partial > k) {
      if (l < r) {
	partial -= line[l++];
      } else if (r < n) {
	++l; ++r;
	partial = line[r];
      } else break;
    } else {
      ++counter;
      begin[r] = l;
      if (l < r) {
	partial -= line[l++];
      } else if (r < n) {
	++l; ++r;
	partial = line[r];
      } else break;
    }
  }
  //traceVec(begin);
  if (counter < m) {
    std::cout << "fail\n";
    return;
  }
  
  std::vector<std::vector<int>> DP(m+1, std::vector<int>(n+1,0));
  for (int i = 1; i <= m; ++i) {
    for (int j = 1; j <= n; ++j) {
      DP[i][j] = DP[i][j-1];
      if (begin[j] != -1) {
	DP[i][j] = std::max(DP[i][j],
			    DP[i-1][begin[j]-1] + j - begin[j] + 1);
      }
    }
  }

  if (DP[m][n] == DP[m-1][n]) std::cout << "fail\n";
  else std::cout << DP[m][n] << std::endl;
  
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) test_case();
}
