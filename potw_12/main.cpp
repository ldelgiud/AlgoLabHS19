#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef std::size_t                                            Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;
typedef K::Point_2 Point;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;


#define trace(x) //std::cout << #x << " = " << x << std::endl
void test_case() {
  int n; K::FT r; std::cin >> n >> r;
  r *= r;
  std::vector<std::pair<Point, Index>> planets;
  planets.reserve(n);
  for (int i = 0; i < n; ++i) {
    int x, y; std::cin >> x >> y;
    planets.push_back({Point(x,y),i});
  }

  int left = 1, right = n;
  int day; 

  while(left < right) {
    day = (left+right)/2;
    
    Delaunay t;
    t.insert(planets.begin()+day, planets.end());
    graph G(n);
    
    for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
      Index i1 = e->first->vertex((e->second+1)%3)->info();
      Index i2 = e->first->vertex((e->second+2)%3)->info();
      if (t.segment(e).squared_length() <= r) {
	boost::add_edge(i1, i2, G);
      }
    }

    std::vector<int> component(n);
    int num = connected_components(G, &component[0]);

    std::vector<int> comp_size(num,0);
    for (int i = 0; i < n; ++i) {
      ++comp_size[component[i]];
    }

    int max_size = 0;
    for (int i = 0; i < num; ++i) {
      max_size = std::max(max_size, comp_size[i]);
    }

    if (day == max_size) break;
    else if (max_size > day) {
      if (left == day) break;
      left = day;
    } else {
      if (right == day)break;
      right = day;
    }
  }

  std::cout << day << std::endl; 
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) test_case();

}
