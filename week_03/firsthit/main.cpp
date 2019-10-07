#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

using namespace std;

void test_case(int n) {
  long x, y, a, b;
  cin >> x >> y >> a >> b;

  K::Point_2 start(x,y), direction(a,b);
  K::Ray_2 ray(start, direction);

  for (int i = 0; i < n; ++i) {
    long r, s, t, u;
    cin >> r >> s >> t >> u;
    
  }
}


int main() {
  int n;
  cin >> n;
  while(n) {
    test_case(n);
    cin >> n;
  }
}
