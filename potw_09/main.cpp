#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Union_find.h>
#include <boost/pending/disjoint_sets.hpp>

typedef CGAL::Exact_predicates_inexact_constructions_kernel  K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                   Fb;  
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>          Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                Delaunay;
typedef Delaunay::Finite_edges_iterator                      EI;
typedef K::Point_2                                           Point;
typedef std::pair<Point,int>                                 IPoint;
typedef boost::disjoint_sets_with_storage<>                  Uf;

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
  Uf ufp(n);
  for (auto e : edges) {
    if (e.sql > p) break;
    ufp.union_set(e.u, e.v);
  }

  K::FT a = 0, b = 0;
  Uf ufa(n), ufb(n);
  int idx_a = 0, idx_b = 0;
  for (int i = 0; i < m; ++i) {
    int x, y, x_, y_; std::cin >> x >> y >> x_ >> y_;
    Point src(x,y); Point trg(x_, y_);
    auto p0 = t.nearest_vertex(src), p1 = t.nearest_vertex(trg);
    K::FT d = 4*std::max(CGAL::squared_distance(p0->point(), src),
			 CGAL::squared_distance(p1->point(), trg));
    if (d <= p && ufp.find_set(p0->info()) == ufp.find_set(p1->info())) {
      std::cout << 'y';
      if (d > b) b = d;
      for (; idx_b < edges.size()
	     && ufb.find_set(p0->info()) != ufb.find_set(p1->info()); ++idx_b) {
	ufb.union_set(edges[idx_b].u, edges[idx_b].v);
      }
    } else std::cout << 'n';
    
    if (d > a) a = d;
    for (; idx_a < edges.size()
	   && ufa.find_set(p0->info()) != ufa.find_set(p1->info()); ++idx_a) {
      ufa.union_set(edges[idx_a].u, edges[idx_a].v);
    }
  }
  
  if (idx_a != 0 && edges[idx_a-1].sql > a) a = edges[idx_a-1].sql;
  if (idx_b != 0 && edges[idx_b-1].sql > b) b = edges[idx_b-1].sql;
  std::cout << std::endl << a << std::endl << b << std::endl;
  
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout << std::fixed << std::setprecision(0);

  int t; std::cin >> t;
  while (t--) test_case();
}
