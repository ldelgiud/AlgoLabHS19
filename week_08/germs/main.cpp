#include <iostream>
#include <vector>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;

int main() {
  int n;
  std::ios_base::sync_with_stdio(false);

  while(true) {
    std::cin>> n;
    if (!n) break;

    int l, b, r, t; std::cin >> l >> b >> r >> t;
    
    std::vector<K::Point_2> pts;
    pts.reserve(n);
    for (int i = 0; i < n; ++i) {
      int x, y; std::cin >> x >> y;
      pts.push_back(K::Point_2(x,y));
    }

    Triangulation t;
    t.insert(pts.begin(), pts.end());

    
  }
  
}
