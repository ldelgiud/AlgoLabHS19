#include<iostream>
#include<vector>
#include<deque>
#include<algorithm>

using namespace std;

#define trace(x) cerr << #x << " = " << x << endl
#define step(x) cerr << "Step " << x << endl

void test_case() {
  int n; cin >> n;
  vector<int> parasols(n);

  for (int i = 0; i < n; ++i) {
      cin >> parasols[i];
  }
  sort(parasols.begin(), parasols.end());

  deque<int> covered;
  covered.push_back(parasols[0]);
  int position = parasols[0];
  int optimal_customers = 0, customers_count = 1;
  int l = 0, r = 1;
  int optimal_dist = 100;
  vector<int> optimal_position;

  while(position <= parasols[n-1]) {

    if (r < n) {
      while (abs(position - parasols[r]) <= 100) {
        covered.push_front(parasols[r]);
        ++r;
        ++customers_count;
        if(r == n) break;
      }
    }
    if (l < n) {
      while (position-100 > parasols[l]) {
        covered.pop_back();
        ++l;
        --customers_count;
        if (l == n) break;
      }
    }

    if (customers_count) {
      int tmp = max(position-covered.back(), covered.front()-position);
      //trace(customers_count);
      //trace(position);
      //trace(tmp);
      if (customers_count == optimal_customers) {
        if (tmp < optimal_dist) {
          optimal_position.clear();
          optimal_position.push_back(position);
          optimal_dist = tmp;
        } else if (tmp == optimal_dist) {
          optimal_position.push_back(position);
        }
      }
      if (customers_count > optimal_customers) {
        optimal_position.clear();
        optimal_position.push_back(position);
        optimal_dist = tmp;
        optimal_customers = customers_count;
      }
    }

    ++position;


  }

  cout << optimal_customers << ' ' << optimal_dist << endl;
  for (int i = 0; i < optimal_position.size(); ++i) {
    cout << optimal_position[i] << ' ';
  }
  cout << endl;
}

int main() {
  std::ios::sync_with_stdio(false);
  int t; cin >> t;
  while(t--) test_case();
}
