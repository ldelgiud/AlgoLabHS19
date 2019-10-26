#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <tuple>
#include <limits>

using namespace std;

#define trace(x) cout << #x << ": " << x << endl

const int INF = 1 << 28;
void test_case() {
  int n, k; cin >> n >> k;

  vector<int> C;
  vector<int> V;
  C.push_back(0);
  V.push_back(0);
  for (int i = 0; i < n; ++i) {
    double c, v;
    cin >> c >> v;
    C.push_back(c);
    V.push_back(v);
  }

  //cost, #ingr
  vector<vector<pair<int,int>>> DP(n+1,vector<pair<int,int>>(k+1,make_pair(0,0)));

  for (int i = 1; i <= k; ++i) {
    DP[0][i].first = INF;
  }
  


  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= k; ++j) {
      int opt = DP[i-1][j].first;
      int ingr = DP[i-1][j].second;
      
      int target_vol = max(0,j-V[i]);
      int tmp = C[i] + DP[i-1][target_vol].first;
      if ((opt > tmp) ||
	  (opt == tmp && ingr <=  DP[i-1][target_vol].second+1)) {
	opt = C[i] + DP[i-1][target_vol].first;
	ingr = DP[i-1][target_vol].second+1;
      }
      tmp = C[i] + DP[i][target_vol].first;
      if ((opt > tmp) ||
	  (opt == tmp && ingr < DP[i][target_vol].second)) {
	opt =  C[i] + DP[i][target_vol].first;
	ingr = DP[i][target_vol].second;
      }
      DP[i][j].first = opt;
      DP[i][j].second = ingr;
    }
  }
  /*
  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= k; ++j) {
      cout << DP[i][j] << '\t';
    }
    cout << endl;
    }*/

  int result = DP[n][k].first;
  int ingr = DP[n][k].second;
  cout << result << ' ' << ingr << endl;
}


int main() {
  std::ios_base::sync_with_stdio(false);
  int t; cin >> t;
  while(t--) test_case();

}
