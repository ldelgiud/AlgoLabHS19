#include<iostream>
#include<set>

using namespace std;

void test_case() {

  int q; cin >> q;
  set<int> M;
  
  for (int i = 0; i < q; ++i) {
    int a, b;
    cin >> a >> b;
    if (!a) {
      M.insert(b);
    } else M.erase(b);
  }

  if (M.empty()) cout << "Empty";
  else {
    for (int i : M) {
      cout << i << ' ';
    }
  }

  cout << endl;
}



int main() {
  int t;
  cin >> t;

  while(t--) {
    test_case();
  }

  }
