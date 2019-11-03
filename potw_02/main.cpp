#include<iostream>
#include<vector>

using namespace std;

#define trace(x) // cout << #x << ": " << x << endl

//int play(int l, int r, int turn);
int n, m, k;

void test_case() {
  // Read Input
  cin >> n >> m >> k;
  vector<int> Coins;
  Coins.reserve(n);
  for (int i = 0; i < n; ++i) {
    int tmp; cin >> tmp;
    Coins.push_back(tmp);
  }

  vector<vector<int>> DP(n,vector<int>(n));

  //Initialize DP
  if (((n-1)%m) == (k%m)) {
    for (int i = 0; i < n; ++i) {
      DP[i][i] = Coins[i];
    }
  } else {
    for (int i = 0; i < n; ++i) {
      DP[i][i] = 0;
    }
  }

  //Calculate entries
  for (int len = 1; len < n; ++len) {
    for(int l = n-1-len; l >= 0; --l) {
      int r = l + len;

      if (((l + (n-r-1))%m) == k) {
        DP[l][r] = max(DP[l+1][r] + Coins[l], DP[l][r-1] + Coins[r]);
      } else {
        DP[l][r] = min(DP[l+1][r], DP[l][r-1]);
      }
    }
  }

  cout << DP[0][n-1] << endl;
}

// int play(int l, int r, int turn) {
//
//   turn = (l + (n-r-1))%m;
//   if (l==r && turn == k) return Coins[l];
//   else if (l==r) return 0;
//   int result;
//
//   if (turn == k) {
//     result = DP[l][r];
//     if (result == -1) {
//       DP[l][r] = max(
//         play(l+1, r, (turn+1)%m) + Coins[l],
//         play(l, r-1, (turn+1)%m) + Coins[r]
//       );
//       result = DP[l][r];
//     }
//   } else {
//     result = DP[l][r];
//     if (result == -1) {
//       DP[l][r] = min(
//         play(l+1, r, (turn+1)%m),
//         play(l, r-1, (turn+1)%m)
//       );
//       result = DP[l][r];
//     }
//   }
//   return result;
// }

int main() {
  std::ios::sync_with_stdio(false);
  int t; cin >> t;
  while(t--) test_case();
}
