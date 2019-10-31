#include<iostream>
#include<deque>
#include<vector>

using namespace std;


void test_case() {
  int n,k;
  cin >> n >> k;
  vector<int> v(n);
  
  for (int i = 0; i < n; ++i) {
    cin >> v[i];
  }

  int sum = k - v[0];
  int best_sum = sum;
  int best_l = 0, best_r = 0;
  deque<int> window;
  int l = 0, r = 0;

  while(r < n && l < n) {

    if (!sum) {
      break;
    } else if (abs(sum) < abs(best_sum)) {
      best_l = l;
      best_r = r;
      best_sum = sum;
    }
    
    while (sum < 0 && l < r) {
      sum += v[l];
      l++;
    }

    if (!sum) {
      break;
    } else if (abs((sum)) < abs(best_sum)) {
      best_l = l;
      best_r = r;
      best_sum = sum;
    }
    
    if (r < (n-1)) {
      sum -= v[++r];
    } else break;
   
  }
  
  if (!sum) {
    cout << l << ' ' << r << endl;
  } else cout << best_l << ' ' << best_r << endl;
}
int main() {
  std::ios::sync_with_stdio(false);
  int t; cin >> t;
  while(t--) test_case();
}
