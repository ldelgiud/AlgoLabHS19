#include<iostream>

using namespace std;

void test_case() {

  string a, b, c, d;
  cin >> a >> b;
  int a_length = a.length();
  int b_length = b.length();
  c = a; d = b;
  cout << a_length << ' ' << b_length << endl;
  cout << a << b << endl;

  for (int i = 0; i < a_length; ++i) {
    c[i] = a[a_length-i-1];
  }
  
  for (int i = 0; i < b_length; ++i) {
    d[i] = b[b_length-i-1];
  }

  char e = c[0];
  c[0] = d[0];
  d[0] = e;

  cout << c << ' ' << d << endl;
   
}


int main() {
  int t;
  cin >> t;

  while(t--) {
    test_case();
    
  }


}
