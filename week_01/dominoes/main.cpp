#include<iostream> 
#include<algorithm>

using namespace std;

void test_case() {
  int n; cin >> n;
  int counter = 0;
  bool falling = true;
  int fall_range = 0;
  
  for (int i = 1; i <= n; ++i) {
    int h_i; cin >> h_i;

    if (falling) {
      fall_range = max(fall_range, i + h_i);
      counter++;
      if ((fall_range > (i + 1)) && (i < n));
      else falling = false;
    }
  }

  cout << counter << endl;
  
}


int main() {
  std::ios::sync_with_stdio(false);
  int t; cin >> t;
  while(t--) test_case();
}
