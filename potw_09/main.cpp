#include <iostream>
#include <vector>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Union_find.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;


void test_case() {
  long long n, m, p;
  std::cin >> n >> m >> p;

  
  std::vector<K::Point_2> jammers;
  jammers.reserve(n);
  for (int i = 0; i < n; ++i) {
    int x, y; std::cin >> x >> y;
    jammers.push_back(K::Point_2(x,y));
  }
  


}

int main() {
  int t; std::cin >> t;

  while (t--) test_case();

}
