#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <bitset>
#include <map>

using namespace std;

#define trace(x) // cout << #x << ": " << x<< endl;
void test_case() {
  int n, m; cin >> n >> m;

  vector<int> b;
  for (int i = 0; i < m; ++i) {
    int b_i; cin >> b_i;
    b.push_back(b_i);
  }

  //on, off
  vector<vector<pair<int,int>>> lights(n);
  vector<int>  rooms(m,0);

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      int on, off; cin >> on >> off;
      lights[i].push_back(make_pair(on,off));
      rooms[j] += on;
    }
  }

  vector<pair<vector<int>,int>> L1(1<<(n/2));
  vector<pair<vector<int>,int>> L2(1<<((n+1)/2));
  for (int i = 0; i < m; ++i) {
    b[i] -= rooms[i];
  }

  for (int i = 0; i < 1<<(n/2); ++i) {
    vector<int> l(m,0);
    int cnt = 0;
    for (int j = 0; j < n/2; ++j) {
      for (int k = 0; k < m; ++k) {
        l[k] += ((i>>j)&1)*lights[j][k].second;
        l[k] -= ((i>>j)&1)*lights[j][k].first;
      }
      cnt += (i>>j)&1;
    }

    L1[i] = make_pair(l,cnt);
  }

  for (int i = 0; i < 1<<((n+1)/2); ++i) {
    vector<int> l(m,0);
    int cnt = 0;
    for (int j = 0; j < (n+1)/2; ++j) {
      for (int k = 0; k < m; ++k) {
        l[k] += ((i>>j)&1)*lights[n/2+j][k].second;
        l[k] -= ((i>>j)&1)*lights[n/2+j][k].first;
      }
      cnt += (i>>j)&1;
    }

    L2[i] = make_pair(l,cnt);
  }

  map<vector<int>,int> ML2;
  for(int i = 0;i < 1<<((n+1)/2); ++i) {
    auto it = ML2.find(L2[i].first);

    if(it == ML2.end()) {
      ML2.insert(make_pair(L2[i].first,L2[i].second));
    } else {
      if(L2[i].second < it->second){
        it->second = L2[i].second;
      }
    }
  }

  int best = n+1;
  for (int i = 0; i < 1<<(n/2); ++i) {
    vector<int> goal = b;

    for (int j = 0; j < m; ++j) {
      goal[j] -= L1[i].first[j];
    }

    auto it = ML2.find(goal);

    if (it != ML2.end()) {
      best = min(best, it->second + L1[i].second);
    }
  }

  if (best == n+1) cout << "impossible" << endl;
  else cout << best << endl;

}

int main() {
  int t; cin >> t;
  while(t--) test_case();


}
