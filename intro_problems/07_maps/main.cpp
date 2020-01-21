#include<iostream>
#include<map>
#include<vector>
#include<algorithm>

using namespace std;

void test_case() {
  int q; cin >> q;
  //Map<key, type>
  multimap<string, int> M;
  
  for (int i = 0; i < q; ++i) {
    int a;
    string b;
    cin >> a >> b;
    if (!a) {
      M.erase(b);
    } else {
      M.insert(pair<string, int>(b, a));
    }
  }

  string s;
  cin >> s;
  auto range = M.equal_range(s);
  if(range.first == range.second) cout << "Empty\n";
  else {
    vector<int> V;
    for (auto i = range.first; i != range.second; ++i) {
      V.push_back(i->second);
    }
    sort(V.begin(), V.end());
    for (int tmp : V) {
      cout << tmp << ' ';
    }
    cout << endl;

  }
		     
  
  
}

int main() {
  int t; cin >> t;

  while(t--) {
    test_case();
  }
}
