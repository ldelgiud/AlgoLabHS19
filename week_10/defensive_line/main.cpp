#include <iostream>
#include <vector>


void test_case() {
  int n, m, k; std::cin >> n >> m >> k;

  std::vector<int> line;
  line.reserve(n);
  for (int i = 0; i < n; ++i) {
    int v; std::cin >> v;
    line.push_back(v);
  }
  

}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) test_case();
}