#include<iostream>
#include<vector>

using namespace std;
int play(int l, int r, int turn);
vector<int> Coins;
vector<vector<int>> Them;
vector<vector<int>> Me;
int n, m, k;

void test_case() {
  cin >> n >> m >> k;

  Coins = vector<int>(n);

  for (int i = 0; i < n; ++i) {
    cin >> Coins[i];
  }

  Them = vector<vector<int>>(n,vector<int>(n,-1));
  Me = vector<vector<int>>(n,vector<int>(n,-1));

  int result = play(0,n-1, 0);

  cout << result << endl;
}

int play(int l, int r, int turn) {

  if (l==r && turn == k) return Coins[l];
  else if (l==r) return 0;
  int result;
  
  if (turn == k) {
    result = Me[l][r];
    if (result == -1) {
      Me[l][r] = max(
        play(l+1, r, (turn+1)%m) + Coins[l],
        play(l, r-1, (turn+1)%m) + Coins[r]
      );
      result = Me[l][r];
    }
  } else {
    result = Them[l][r];
    if (result == -1) {
      Them[l][r] = min(
        play(l+1, r, (turn+1)%m),
        play(l, r-1, (turn+1)%m)
      );
      result = Them[l][r];
    }
  }
  return result;
}

int main() {
  std::ios::sync_with_stdio(false);
  int t; cin >> t;
  while(t--) test_case();
}
