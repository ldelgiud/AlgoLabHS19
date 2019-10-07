#include <iostream>
#include <vector>
#include <utility>
#include <set>
using namespace std;

vector<vector<int>> G;
int n;
vector<pair<int,bool>> DP;
vector<int> C;

int play(int node);

void test_case() {
  cin >> n;
  
  set<int> finish;
  for (int i = 0; i < n; ++i) {
    finish.insert(i);
  }

  G.clear();
  G = vector<vector<int>>(n);
  for (int i = 0; i < n-1; ++i) {
    int a, b;
    cin >> a >> b;
    //cout << "a: " << a << ".. b: " << b << endl;

    G[a].push_back(b);
    finish.erase(a);
  }

  C.clear();
  C.reserve(n);
  for (int i = 0; i < n; ++i) {
    int tmp; cin >> tmp;
    C.push_back(tmp);
  }
  
  //init DP
  DP.clear();
  DP = vector<pair<int,bool>>(n, make_pair(-1,false));
  for (int i: finish) {
    DP[i] = make_pair(C[i], true);
  }

  int res = play(0);
  cout << res << endl;
}

int play(int node) {
  //cout << "node " << node << endl; 
  if (G[node].size() == 0) return C[node];

  if (DP[node].first == -1) {
    int option1 = C[node];
    for (int v: G[node]) {
      //cout << "v " << v << endl;
      if (G[v].size() != 0){
	//cout << "size " << G[v].size() << endl;
	for (int u: G[v]) {
	  //cout << "u " << u << endl;
	  option1 += play(u);
	}
      } 
    }
    int option2 = 0;
    bool flag = false;
    int minCost = 1 << 28;
    for (int v: G[node]) {
      if (DP[node].second) flag = true;
      option2 += play(v);
      if (minCost > C[v]) minCost = C[v];
    }

    if (!flag) option2 += minCost;
 
    if (option1 < option2) {
      DP[node].second = true;
      DP[node].first = option1;
    } else {
      DP[node].second = false;
      DP[node].first = option2;
    }
  }
  
  return DP[node].first;


}

int main() {
  int t; cin >> t;
  while(t--) test_case();
}
