#include <iostream>
#include <string>
#include <map>
#include <vector>

void test_case() {
  int n, q; std::cin >> n >> q;
  // <name(key), idx >
  std::map<std::string, int> map;
  std::vector<std::string> names;
  std::vector<int> ages;
  for (int i = 0; i < n; ++i) {
    std::string s;
    long a;
    std::cin >> s >> a;
    map.insert({s,i});
    names.push_back(s);
    ages.push_back(a);
  }

  std::vector<int> pred(n,-1);
  for (int i = 0; i < n-1; ++i) {
    std::string s, p; std::cin >> s >> p;
    int offspring = map.find(s)->second;
    int ancestor = map.find(p)->second;
    pred[offspring] = ancestor;
  }
  
  for (int i = 0; i < q; ++i) {
    std::string name;
    int age;
    std::cin >> name >> age;

    int idx = map.find(name)->second;
    while (pred[idx] != -1 && ages[pred[idx]] <= age) {
      idx = pred[idx];
    }
    std::cout << names[idx] << ' ';
  }

  std::cout << std::endl;
  
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) test_case(); 
}
