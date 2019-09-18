#include<iostream>
#include<vector>

using namespace std;

void test_case() {
  int n;
  cin >> n;
  vector<int> v(n);

  
  for(int i = 0; i < n; ++i) {
    int tmp; cin >> tmp;
    v[i] = tmp;
  }
  
  int d, a, b;
  cin >> d >> a >> b;
  
  v.erase(v.begin() + d);
  v.erase(v.begin() + a, v.begin() + b + 1);
    
  if (v.empty()) {
    cout << "Empty\n";
  } else {
    for(int tmp : v) {
        std::cout << tmp << ' ';
    }
    cout << endl;
  }
  
}


int main() {
  int t;
  cin >> t;

  while(t--) {
    test_case();
  }


}
