#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <tuple>
void test_case() {

  int n; std::cin >> n;
  std::vector<int> planks;
  planks.reserve(n);
  int len = 0;
  for (int i= 0; i < n; ++i) {
    int l_i;
    std::cin >> l_i;
    planks.push_back(l_i);
    len += l_i;
  }

  if (len%4 != 0) {
    std::cout << 0 << std::endl;
    return;
  }

  std::vector<std::tuple<int,int,int,int>> L1(1<<(n/2));
  std::vector<std::tuple<int,int,int,int>> L2(1<<((n+1)/2));


  
}


int main() {
  int t; std::cin >> t;
  while(t--) test_case();

}
