#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <tuple>
#include <bitset>


#define trace(x) //std::cout << #x << ": " << x << std::endl
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
  int sum = len/4;

  int n1= n/2;
  int n2 = (n+1)/2;
  std::vector<std::tuple<int,int,int,int>> L1(1<<(n1*2),std::make_tuple(0,0,0,0));
  std::vector<std::tuple<int,int,int,int>> L2(1<<(n2*2),std::make_tuple(0,0,0,0));


  //Buid L1
  for (int i = 0; i < 1<<(n1*2); ++i) {
    std::vector<int> tmp(4,0);
    for(int j = 0; j < n2; ++j){
      int idx = (i & (3<<2*j)) >> 2*j;
      tmp[idx] += planks[j];
    }

    if(tmp[0] <= sum && tmp[1] <= sum && tmp[2] <= sum && tmp[3] <= sum) {
      L1[i] = std::make_tuple(tmp[0],tmp[1],tmp[2],tmp[3]);

    }
  }

  //Build l2
  for (int i = 0; i < 1<<(n2*2); ++i) {
    std::vector<int> tmp(4,0);

    for(int j = 0; j < n2; ++j){
      int idx = (i & (3<<2*j)) >> 2*j;
      tmp[idx] += planks[n2+j];
    }

    if(tmp[0] <= sum && tmp[1] <= sum && tmp[2] <= sum && tmp[3] <= sum) {
      L2[i] = std::make_tuple(tmp[0],tmp[1],tmp[2],tmp[3]);
    }
  }

  std::sort(L2.begin(), L2.end());

  long res = 0;
  for (auto t: L1) {
    auto key = std::make_tuple(
      sum - std::get<0>(t),
      sum - std::get<1>(t),
      sum - std::get<2>(t),
      sum - std::get<3>(t));

      auto bounds = std::equal_range(L2.begin(),L2.end(),key);
      res += std::distance(bounds.first,bounds.second);

  }

  std::cout << res/(long)24 << std::endl;


}


int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) test_case();

}
