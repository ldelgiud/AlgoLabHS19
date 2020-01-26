#include <iostream>
#include <vector>

//<direction, weight>
typedef std::pair<int, long> Edge;
typedef std::vector<std::vector<Edge>> Graph;

Graph G;
std::vector<std::vector<long>> DP;

#define trace(x) //std::cout << #x << " = " << x << std::endl
#define step(x)// std::cout << "STEP: " << x << std::endl
// j = moves_left
long play(int u, int j) {
  
  if (DP[u][j] != -1) return DP[u][j];
  
  long max = 0;
  if (G[u].size()==0) {
    max = play(0, j);
  } else {
    for (Edge v : G[u]) {
      max = std::max(max, play(v.first,j-1) + v.second);
    }
  }
  
  DP[u][j] = max;
  return max;
}

void test_case() {
  int n, m ,k; long x; std::cin >> n >> m >> x >> k;
  G.clear(); DP.clear();
  G = Graph(n);
  DP = std::vector<std::vector<long>>(n, std::vector<long>(k+1,-1));
  
  for (int i = 0; i < m; ++i) {
    int u, v; long p; std::cin >> u >> v >> p;
    G[u].push_back({v, p});
  }

  for (int i = 0; i < n; ++i) DP[i][0] = 0;

  for (int i = 0; i <= k; ++i) {
    if (play(0,i) >= x) {
      std::cout << i << std::endl;
      return;
    }
  }
  std::cout << "Impossible\n";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) test_case();
}
