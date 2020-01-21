#include<iostream>
#include<vector>
#include<utility>
#include<stack>
#include<algorithm>

using namespace std;

void test_case() {

  int n,m,v;
  cin >> n >> m >> v;

  vector<vector<int>> G(n);
  vector<pair<int,int>> order(n, make_pair(-1,-1));
  vector<bool> visited(n,false);
  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    G[a].push_back(b);
    G[b].push_back(a);
  }

  for(int i = 0; i < n; ++i) {
    sort(G[i].begin(), G[i].end());
  }
  
  stack<int> S;
  S.push(v);
  int count = 0;
  order[v].first = count++;
  visited[v] = true;
  //cout << "count now is: " << count << endl << "order instead is: " << order[0].first;

  while(!S.empty()) {
 
    v = S.top();
    bool flag = false;
    for(int u : G[v]) {
      if(!visited[u]) {
	S.push(u);
	visited[u] = true;
	order[u].first = count++;
	flag = true;
	break;
      }
    }
    if(!flag) {
      order[v].second = count++;
      S.pop();
    }
  }

  for(auto tmp : order) {
    cout << tmp.first << ' ';
  }
  cout << endl;
  for(auto tmp : order) {
    cout << tmp.second << ' ';
  }
  cout << endl;
 
}


int main() {
  int t; cin >> t;
  
  while(t--) {
    test_case();
  }

}
