#include<iostream>
#include<vector>
#include<utility>
#include<queue>
#include<algorithm>

using namespace std;

void test_case() {

  int n,m,v;
  cin >> n >> m >> v;

  vector<vector<int>> G(n);
  vector<int> dist(n, -1);
  vector<bool> visited(n,false);

  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    G[a].push_back(b);
    G[b].push_back(a);
  }

  queue<int> S;
  S.push(v);
  dist[v] = 0;
  visited[v] = true;
  //cout << "count now is: " << count << endl << "order instead is: " << order[0].first;

  while(!S.empty()) {
 
    v = S.front();
    S.pop();

    for(int u : G[v]) {
      if(!visited[u]) {
	S.push(u);
	visited[u] = true;
	dist[u] = dist[v]+1;
      }
    }
  }

  for(int tmp : dist) {
    cout << tmp << ' ';
  }
  cout << endl;
 
}


int main() {
  int t; cin >> t;
  
  while(t--) {
    test_case();
  }

}
