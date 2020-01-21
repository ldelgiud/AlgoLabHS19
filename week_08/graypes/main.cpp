#include <iostream>
#include <vector>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Delaunay_triangulation_2.h>
typedef CGAL::Exact_predicates_inexact_constructions_kernel IK;
typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt EK;

double ceil_to_double(EK::FT const & x) {
  double a = std::ceil(CGAL::to_double(x));
  while (a < x)
    a += 1;
  while (a-1 >= x) a -= 1;
  return a;
}

int main() {
  int n;
  
  while(true) {
    std::cin >> n;
    if (!n) break;

    std::vector<IK::Point_2> v;
    v.reserve(n);
    for (int i = 0; i < n; ++i) {
      int x, y; std::cin >> x >> y;
      IK::Point_2 p(x,y);
      v.push_back(p);
    }

    CGAL::Delaunay_triangulation_2<IK> trg;
    trg.insert(v.begin(), v.end());

    IK::FT min_sqrd_dist = std::numeric_limits<IK::FT>::max();
    for (auto e = trg.finite_edges_begin(); e != trg.finite_edges_end(); ++e) {
      min_sqrd_dist = std::min(min_sqrd_dist,
			  trg.segment(*e).squared_length());
    }

    
    EK::FT res =50* CGAL::sqrt(EK::FT(min_sqrd_dist));

    std::cout << ceil_to_double(res) << std::endl;
  }
}
