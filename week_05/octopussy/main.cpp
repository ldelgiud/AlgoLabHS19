#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <tuple>

using namespace std;

void test_case() {
  int n; cin >> n;
  //timer, index, detonated
  vector<tuple<int,int,bool>> bombs;
  bombs.reserve(n);
  vector<pair<int,bool>> reachable;
  for (int i = 0; i < n; ++i) {
    int t;
    cin >>t;
    bombs.push_back(make_tuple(t, i, false));
    reachable.push_back(make_pair(i, i>=(n-1)/2));
  }

  sort(bombs.begin(), bombs.end());
  int detonated = 0;
  int i = 0;
  int time = 0;

  vector<bool> done(n,false);
  while (detonated < n) {
    int target = 0;
    for (; i < n; ++i) {
      if (!get<2>(bombs[i])) {
        target = get<1>(bombs[i]);
        break;
      }
    }
    
  }


}


int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  while (t--) test_case;
}
