#include<iostream>
#include <iomanip>      // std::setprecision

using namespace std;

void test_case() {
  int a;
  long long b;
  string  c;
  double d;

  cin >> a >> b >> c >> d; 
  cout << a << ' ' << b << ' ' << c << ' ' << d << endl;
  
}


int main() {
  
  int t; cin >> t;
  std::cout << std::setprecision(3);
  while(t--) {
    test_case();
  }
}
