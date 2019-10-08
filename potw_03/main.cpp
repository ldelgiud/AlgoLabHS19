#include <iostream>
#include <vector>
#include <utility>
#include <set>

using namespace std;

// Used for debugging
#define step(x) cout << "Step (" << x << ")" << endl
#define trace(x) cout << #x << " = " << x << endl

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

  //Leaves
  for (int i: finish) {
    DP[i] = make_pair(C[i], true);
  }
  
  //Parents of leaves
  for (int i = 0; i < n; ++i) {
    bool flag = true;
    int cost = 0;
    for (int v: G[i]) {
      cost += C[v];
      if (G[v].size() > 0) flag = false;
    }
    if (flag && DP[i].first == -1) {
      if (cost >= C[i]) {
	DP[i].first = C[i];
	DP[i].second = true;
      } else {
        DP[i].first = cost;
	DP[i].second = false;
      }
    }
  }
  
  int res = play(0);
  cout << res << endl;
  /*
  for (auto it: DP) {
    cout << it.first << ' ';
  }*/
}

int play(int node) {
  
  if (DP[node].first == -1) {
    int option1 = C[node];
    for (int v: G[node]) {
      if (G[v].size() != 0){
	for (int u: G[v]) {
	  option1 += play(u);
	}
      } 
    }
    
    int option2 = 0;
    bool flag = false;
    int minCost = 1 << 28;
    for (int v: G[node]) {
      option2 += play(v);
      if (DP[v].second) flag = true;     
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
  std::ios_base::sync_with_stdio(false);
  int t; cin >> t;
  while(t--) test_case();
}
