#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>


#define trace(x)// std::cout << #x << " = " << x << std::endl
#define step(i) // std::cout << "step: " << i << std::endl
int n, m;

bool possible(int r, std::vector<int> w, std::vector<int> s) {
  int i = 0, j = 0;
  while (i < n && j < m) {
    if (w[j] <= s[i]) {
      ++i;
      j += r;
    } else return false;
  } return j >= m;

}

void test_case() {
 std::cin >> n >> m;

  std::vector<int> strength;
  strength.reserve(n);
  for (int i = 0; i < n; ++i) {
    int s; std::cin >> s;
    strength.push_back(s);
  }
  
  std::vector<int> weight;
  weight.reserve(m);
  for (int i = 0; i < m; ++i) {
    int w; std::cin >> w;
    weight.push_back(w);
  }

  std::sort(strength.begin(), strength.end(), std::greater<int>());
  std::sort(weight.begin(),   weight.end(),   std::greater<int>()); 

  for (int w: weight) {
    if (w > strength[0]) {
      std::cout << "impossible\n";
      return;
    }
  }

  int r = 1;
  while (!possible(r, weight, strength)) {
    r*=2;
  }
  
  int l = (r/2) + 1;
  
  while (r > l) {
    int count = r - l;
    int step = count / 2;
    int mid = l+step;
    step(step);
    trace(r);
    trace(l);
    if (possible(mid, weight, strength)) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }

  std::cout << 3*r - 1 << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) test_case();
}
