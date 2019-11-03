#include<iostream>
#include<vector>

using namespace std;

#define trace(x)// cout << #x << ": " << x << endl

int play(int l, int r, int turn);
vector<int> Coins;
vector<vector<int>> DP;
int n, m, k;

void test_case() {
  cin >> n >> m >> k;
  Coins = vector<int>(n);
  trace(n);
  for (int i = 0; i < n; ++i) {
    cin >> Coins[i];
  }

  DP = vector<vector<int>>(n,vector<int>(n,0));

  for (int len = 0; len < n; ++len) {
    for(int row = 0; row < n; ++row) {
      int l = row;
      int r = row + len;
      if (r >= n) continue;

      int turn = (l + (n-r-1))%m;
      trace(len);
      trace(row);
      if (l==r && turn == k){
        DP[l][r] = Coins[l];
        continue;
      }
      else if (l==r) {
        DP[l][r] = 0;
        continue;
      }

      if (turn == k) {
        DP[l][r] = max(DP[l+1][r] + Coins[l], DP[l][r-1] + Coins[r]);
      } else {
        DP[l][r] = min(DP[l+1][r], DP[l][r-1]);
      }
    }
  }

  int result = DP[0][n-1];
  cout << result << endl;
}

int play(int l, int r, int turn) {

  turn = (l + (n-r-1))%m;
  if (l==r && turn == k) return Coins[l];
  else if (l==r) return 0;
  int result;

  if (turn == k) {
    result = DP[l][r];
    if (result == -1) {
      DP[l][r] = max(
        play(l+1, r, (turn+1)%m) + Coins[l],
        play(l, r-1, (turn+1)%m) + Coins[r]
      );
      result = DP[l][r];
    }
  } else {
    result = DP[l][r];
    if (result == -1) {
      DP[l][r] = min(
        play(l+1, r, (turn+1)%m),
        play(l, r-1, (turn+1)%m)
      );
      result = DP[l][r];
    }
  }
  return result;
}

int main() {
  std::ios::sync_with_stdio(false);
  int t; cin >> t;
  while(t--) test_case();
}
