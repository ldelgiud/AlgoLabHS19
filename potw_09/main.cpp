#include <iostream>
#include <vector>
#include <algorithm>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Union_find.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel  K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                   Fb;  
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>          Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                Delaunay;
typedef Delaunay::Finite_edges_iterator                      EI;
typedef K::Point_2                                           Point;
typedef std::pair<Point,int>                                 IPoint;

struct Edge {
  Edge(int u_, int v_, K::FT sql_) : u(u_), v(v_), sql(sql_) {}
  int u, v;
  K::FT sql;
  
};

inline bool operator<(const Edge& e, const Edge& f) { return e.sql < f.sql; }

void test_case() {
  long long n, m, p;
  std::cin >> n >> m >> p;

  
  std::vector<IPoint> jammers;
  jammers.reserve(n);
  for (int i = 0; i < n; ++i) {
    int x, y; std::cin >> x >> y;
    jammers.push_back({Point(x,y),i});
  }

  Delaunay t;
  t.insert(jammers.begin(), jammers.end());


  std::vector<Edge> edges;
  edges.reserve(3*n);

  for (EI e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
    edges.push_back(Edge(e->first->vertex((e->second+1)%3)->info(),
			 e->first->vertex((e->second+2)%3)->info(),
			 t.segment(e).squared_length()));

  }
  std::sort(edges.begin(), edges.end());

  
  for (int i = 0; i < m; ++i) {
    int x, y, x_, y_; std::cin >> x >> y >> x_ >> y_;
    Point s(x,y); Point t(x_, y_);
    
  }


}

int main() {
  int t; std::cin >> t;

  while (t--) test_case();

}
