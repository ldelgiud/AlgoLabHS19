#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
// we want to store an index with each vertex
typedef std::pair<int, bool>                                   info_t;
typedef CGAL::Triangulation_vertex_base_with_info_2<info_t,K>  Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;
typedef Delaunay::Vertex_handle vhandle_t;
typedef Delaunay::Vertex_circulator vcirculator_t;
typedef K::Point_2 Point;

bool interferes(Delaunay const &trg, K::FT r) {
  for (auto e = trg.finite_edges_begin(); e != trg.finite_edges_end(); ++e) {
    if (trg.segment(*e).squared_length() <= r) return true;
  }
  return false;
}

bool color(Delaunay &trg, K::FT r) {

  for (auto v =trg.finite_vertices_begin(); v != trg.finite_vertices_end(); ++v) {
    v->info() = {0, false};
  }

  int components = 0;

  Delaunay red, blue;
  for (auto v =trg.finite_vertices_begin(); v != trg.finite_vertices_end(); ++v) {
    if (!v->info().first) {
      v->info().first = ++components;
      std::vector<vhandle_t> stack(1, v);
      do {
	vhandle_t h = stack.back();
	stack.pop_back();
	vcirculator_t c = trg.incident_vertices(h);
	do {
	  if (!trg.is_infinite(c) &&
	      CGAL::squared_distance(h->point(), c->point()) <= r) {
	    if (c->info() == h->info()) return false;
	    if (c->info().first == 0) {
	      stack.push_back(c);
	      c->info() = {components, !h->info().second};
	    }
	  }
	} while (++c != trg.incident_vertices(h));
      } while (!stack.empty());

    }
    if (v->info().second) red.insert(v->point());
    else blue.insert(v->point());
  }

  return !interferes(red, r) && !interferes(blue, r);
}
  
void test_case() {
  int n, m;
  K::FT r;
  std::cin >> n >> m >> r;
  r *= r;
  std::vector<Point> stations;
  stations.reserve(n);

  for (int i = 0; i < n; ++i) {
    int x, y; std::cin >> x >> y;
    stations.push_back(Point(x,y));
  }

  Delaunay trg(stations.begin(), stations.end());
  bool success = color(trg, r);
  
  for (int i = 0; i < m; ++i) {
    int x, y; std::cin >> x >> y;
    Point holmes(x,y);
    std::cin >> x >> y;
    Point watson(x,y);

    if (success) {
      if (CGAL::squared_distance(holmes, watson) <= r) {
	std::cout << "y";
	continue;
      }

      auto station_h = trg.nearest_vertex(holmes);
      auto station_w = trg.nearest_vertex(watson);
      if (station_h->info().first == station_w->info().first &&
	  CGAL::squared_distance(holmes, station_h->point()) <= r &&
	  CGAL::squared_distance(watson, station_w->point()) <= r) {
	std::cout << "y"; continue;
      } else {
	std::cout << "n";
      }
    } else {
      std::cout << "n";
    }
  }
  std::cout << std::endl;
  
}
int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) test_case();
}
