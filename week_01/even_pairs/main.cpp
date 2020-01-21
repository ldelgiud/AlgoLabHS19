#include<iostream>

void test_case() {
  int n; std::cin >> n;
  int even = 1, odd = 0, sum = 0;
  
  for (int i = 0; i < n; i++) {
    int tmp;
    std::cin >> tmp;
    sum += tmp;
    if (!(sum % 2)) ++even;
    else ++odd;
  }
  
  int total = even*(even-1)/2 + odd*(odd-1)/2;
  std::cout << total << std::endl;
}

int main() {
  std::ios::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) test_case();
}

