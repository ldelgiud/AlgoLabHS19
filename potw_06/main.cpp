#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <map>

using namespace std;

int earliest_df(vector<pair<int, int>>& jedi, int min, int max) {
  int a = min;
  int n = 0;
  for(auto it = jedi.begin(); it != jedi.end(); ++it) {
    if(it->first > a && it->second < max) {
      a = it->second;
      ++n;
    }
  }
  return n;
}

void test_case() {
  int n, m; cin >> n >> m;
  map<int,int> diff;
  vector<pair<int,int>> jedi;
  jedi.reserve(n);
  
  for (int i = 0; i < n; ++i) {
    int a, b; cin >> a >> b;
    jedi.push_back(make_pair(a-1,b-1));

    ++diff[a];
    --diff[b];
    if(a > b) ++diff[0]; 
  }

  int s = 0;
  int count = 0;
  int opt = n;
  for (auto it = diff.begin(); it != diff.end(); ++it) {
    count += it->second;
    if (count <= 10 && count < opt) {
      s = it->first;
      opt = count;
    
    }
  }

  vector<pair<int,int>> overlap;
  vector<pair<int,int>> other;
  
  for(int i = 0; i < n; i++) {
    int a = jedi[i].first, b = jedi[i].second;

    if(a > s) jedi[i].first = a - s;
    else jedi[i].first = a - s + m;
    if(b > s) jedi[i].second = b - s;
    else jedi[i].second = b - s + m;
 
    if((a <= b && a <= s && s <= b) ||
       (a > b && (a <= s || s <= b))) {
      overlap.push_back(jedi[i]);
    } else {
      other.push_back(jedi[i]);
    }
  }

  
  sort(other.begin(), other.end(), [](pair<int, int> j1, pair<int, int> j2) {
      return j1.second < j2.second;
    });

  int sol = earliest_df(other, -1, m);
  for(auto it = overlap.begin(); it != overlap.end(); it++) {
    sol = max(sol, earliest_df(other, it->second % m, it->first) + 1);
  }
  
  cout << sol << endl;

}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  while(t--) test_case();
}
