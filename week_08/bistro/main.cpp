#include <iostream>
#include <vector>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Voronoi_diagram_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout << std::fixed << std::setprecision(0);
  int n;

  while(true) {
    std::cin >> n;
    if (!n) break;

    std::vector<K::Point_2> v;
    v.reserve(n);
    
    for (int i = 0; i < n; ++i) {
      int x,y; std::cin >> x >> y;
      v.push_back(K::Point_2(x,y));
    }

    Triangulation t;
    t.insert(v.begin(), v.end());
    
    int m; std::cin >> m;


    for (int i = 0; i < m; ++i) {
      int x, y; std::cin >> x >> y;
      K::Point_2 p(x,y);

      K::FT sqrd_dist = CGAL::squared_distance(p, t.nearest_vertex(p)->point());
      std::cout << sqrd_dist << std::endl;
    }
  }
}
