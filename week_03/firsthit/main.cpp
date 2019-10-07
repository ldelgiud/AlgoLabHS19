#include <iostream>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <limits>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;

using namespace std;

double floor_to_double(const K::FT& x) {
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

void test_case(int n) {
  long x, y, a, b;
  cin >> x >> y >> a >> b;

  double best_sqrd_dist = numeric_limits<double>::max();
  K::Point_2 start(x,y), direction(a,b);
  K::Ray_2 ray(start, direction);
  
  bool flag = false;
  K::Point_2 temp(12,12);
  
  for (int i = 0; i < n; ++i) {
    long r, s, t, u;
    cin >> r >> s >> t >> u;
    //cout << i << endl;
     K::Point_2 begin(r,s), end(t,u);
    K::Segment_2 seg(begin, end);
    if (CGAL::do_intersect(seg, ray)) {
      auto o = CGAL::intersection(seg, ray);
      if (const K::Point_2* op = boost::get<K::Point_2>(&*o)) {
	 K::FT d = CGAL::squared_distance(*op,start);
	 if (floor_to_double(d) < best_sqrd_dist) {
	   best_sqrd_dist = floor_to_double(d);
	   flag = true;
	   temp = *op;
	 }
      }
    }
  }

  if (flag) cout << floor_to_double(temp.x()) << ' ' << floor_to_double(temp.y()) << endl;
  else cout << "no\n";
}


int main() {
  int n;
  cin >> n;
  while(n) {
    test_case(n);
    cin >> n;
  }
}
