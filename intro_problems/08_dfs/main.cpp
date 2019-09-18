#include<iostream>
#include<vector>

using namespace std;

void test_case() {

  int n,m,v;
  cin >> n >> m >> v;

  vector<vector<int>> G(n);
  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;

    G[a].push_back(b);
    G[b].push_back(a);
  }
}


int main() {
  int t; cin >> t;

  while(t--) {
    test_case();
  }

}
