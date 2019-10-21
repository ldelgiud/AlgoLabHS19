#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <tuple>
using namespace std;


void test_case() {
  int n, k; cin >> n >> k;

  vector<tuple<double,double,double>> ingr;
  for (int i = 0; i < n; ++i) {
    double c, v;
    cin >> c >> v;
    ingr.push_back(make_tuple(c/v,c,v));
  }

  sort(ingr.begin(),ingr.end());
  int bev_cnt = 0;
  int cost = n / ingr[0] + 1;
  for (int i = 0; i < n; ++i)  {
    


  }

  cout << cost << ' ' << bev_cnt << endl;
}


int main() {
  int t; cin >> t;
  while(t--) test_case();

}
