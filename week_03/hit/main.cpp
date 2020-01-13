#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace std;
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
bool test_case(int n) {

  long a, b, x, y; cin >> x >> y >> a >> b;

  K::Point_2 start(x,y), direction(a,b);
  K::Ray_2 ray(start, direction);
  bool intersect = false;
  for (int i = 0; i < n; ++i) {
    long r, s, t, u;
    cin >> r >> s >> t >> u;
    
    K::Point_2 begin(r,s), end(t,u);
    K::Segment_2 segment(begin,end);

    if (!intersect && CGAL::do_intersect(ray, segment)) {
      intersect = true;
    }
  }

  return intersect;
}

int main() {
  int n;
  cin >> n;
  while(n) {
    if (test_case(n)) cout << "yes\n";
    else cout << "no\n";
    cin >> n;
  }
}
