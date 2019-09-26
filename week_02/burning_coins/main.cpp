#include<iostream>
#include<vector>

using namespace std;

vector<vector<int>> DP_me;
vector<vector<int>> DP_him;
vector<int> T;
int n;
static bool MINE = true;
static bool HIS = false;

int best_strat(bool turn, int l, int r);

void test_case() {
  cin >> n;

  T.clear();
  T.reserve(n);
  for (int i = 0; i < n; ++i) {
    int tmp; cin >> tmp;
    T.push_back(tmp);
  }
  DP_me.clear();
  DP_him.clear();
  for (int i = 0; i < n; ++i) {
    DP_me.push_back(vector<int>(n,-1));
    DP_him.push_back(vector<int>(n,-1));
  }


  int res = best_strat(MINE,0,n-1);

  cout << res << endl;
}

int best_strat(bool turn, int l, int r) {

  if (l == r) {
    if (turn == MINE) return T[l];
    else return 0;
  }

  if (turn == MINE) {
    if (DP_me[l][r] == -1) {
      DP_me[l][r] = max( T[l] + best_strat(HIS, l+1, r),
                        T[r] + best_strat(HIS,l,r-1));
      return DP_me[l][r];
    } else return DP_me[l][r];
  } else {
    if (DP_him[l][r] == -1) {
      DP_him[l][r] = min(best_strat(MINE, l+1, r), best_strat(MINE,l,r-1));
      return DP_him[l][r];
    } else return DP_him[l][r];
  }
}

int main() {
  int t; cin >> t;
  while(t--) test_case();
}
