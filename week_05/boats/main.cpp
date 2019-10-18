#include <iostream>
#include <vector>
#include <limits>
#include <utility>
#include <algorithm>
using namespace std;

#define trace(x)// cout << #x << ": " << x << endl
void test_case() {
  int n; cin >> n;
  //boat, pole
  vector<pair<int, int>> boats;
  boats.reserve(n);

  for (int i = 0; i < n; ++i) {
    int l, p;
    cin >> l >> p;
    boats.push_back(make_pair(l,p));
  }

  sort(boats.begin(), boats.end(),
    [] (pair<int,int> a, pair<int,int> b) {
        return a.second < b.second;
    });


    int tot=1;
    int pos = boats[0].second;

    // Idea:
    // pick the one which ends first
    int i=1;
    while(i<n){
      int idx=-1;
      int best = numeric_limits<int>::max();

      for(int j = i; j < n; j++) {
        if(boats[j].second >= best) break;
        else if(boats[j].second >= pos){
          int tmp = max(pos + boats[j].first, boats[j].second);
          if (tmp < best) {
            best = tmp;
            idx = j;
          }
        }
      }

      if (idx == -1) break;
      pos = best;
      tot++;
      i = idx + 1;
    }

  cout << tot << endl;
}


int main() {
  int t; cin >> t;
  while(t--) test_case();

}
