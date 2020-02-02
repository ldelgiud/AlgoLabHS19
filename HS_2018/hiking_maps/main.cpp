#include <iostream>
#include <cassert>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Line_2 Line;

struct Triangle {
  Line e1, e2, e3;

  Triangle(P p0, P p1, P p2, P p3, P p4, P p5) {
    if (CGAL::left_turn(p0,p1,p2)) e1 = Line(p0,p1);
    else e1 = Line(p1,p0);
    if (CGAL::left_turn(p2,p3,p4)) e2 = Line(p2,p3);
    else e2 = Line(p3,p2);
    if (CGAL::left_turn(p4,p5,p0)) e3 = Line(p4,p5);
    else e3 = Line(p5,p4);
  }
};

bool contains(Triangle t, P p) {
  return !t.e1.has_on_negative_side(p)
      && !t.e2.has_on_negative_side(p)
      && !t.e3.has_on_negative_side(p);
}

bool contains_leg(Triangle t, P p1, P p2) {
  return contains(t, p1) && contains(t, p2);
}
void test_case() {
  int m, n; std::cin >> m >> n;

  std::vector<P> path;
  path.reserve(m);
  for (int i = 0; i < m; ++i) {
    K::FT x, y; std::cin >> x >> y;  
    path.push_back(P(x,y));
  }

  std::vector<Triangle> T;
  for (int i = 0; i < n; ++i) {
    P p0,p1,p2,p3,p4,p5; std::cin >> p0 >> p1 >> p2 >> p3 >> p4 >> p5;
    Triangle t(p0,p1,p2,p3,p4,p5);
    T.push_back(t);
  }

  std::vector<std::vector<int>> contains(n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m-1; ++j) {
      if (contains_leg(T[i], path[j], path[j+1])) contains[i].push_back(j);
    }
  }

  int b = 0, e = 1;
  int best = 1 << 20, cov_cnt = 0; 
  std::vector<int> covered(m-1,0);
  for (int tmp : contains[0]) {
    ++covered[tmp];
    ++cov_cnt;
  }
  
  while (true) {
    assert(cov_cnt < m);
    if (cov_cnt < m-1) {
      if (e < n) {
	for (int tmp : contains[e++]) {
	  if (!covered[tmp]++) ++cov_cnt;
	}
      } else {
	break;
      }
    } else if (cov_cnt == m-1) {
      best = std::min(e-b, best);
      for (int tmp : contains[b++]) {
	if (!--covered[tmp]) --cov_cnt;
      }	
    } 
  }

  std::cout << best << std::endl;
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) test_case();
}
