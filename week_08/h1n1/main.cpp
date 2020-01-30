#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <queue>
typedef long long ll;

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>

// Epic kernel is enough, no constructions needed, provided the squared distance
// fits into a double (!)
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
// we want to store an index with each vertex
typedef CGAL::Triangulation_vertex_base_2<K>      Vb;
typedef CGAL::Triangulation_face_base_with_info_2<ll,K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;
typedef K::Point_2 P;


#define trace(x) std::cout << #x <<" = " << x << std::endl;

int main() {
  std::ios_base::sync_with_stdio(false);

  while(true) {
    int n; std::cin >> n;
    if (!n) break;

    std::vector<P> points; points.reserve(n);
    for (int i = 0; i < n; ++i) {
      int x, y; std::cin >> x >> y;
      points.push_back(P(x,y));
    }
    Delaunay t;
    t.insert(points.begin(), points.end());

    std::queue<Delaunay::Face_handle> Q;
    for (auto it = t.all_faces_begin(); it != t.all_faces_end(); ++it) {
      if (t.is_infinite(it)) {
	auto v1 = it->vertex(0), v2 = it->vertex(1);
	if (!t.is_infinite(it,1)) {v1 = it->vertex(2); v2 = it->vertex(0);}
	if (!t.is_infinite(it,2)) {v1 = it->vertex(0); v2 = it->vertex(1);}

	ll dist = CGAL::squared_distance(v1->point(), v2->point());
	it->info() = dist;
	Q.push(it);
      } else it->info() = 0;
    }

    while (!Q.empty()) {
      auto u = Q.front(); Q.pop();
      
      for (int i = 0; i < 3; ++i) {
	auto v = u->neighbor(i);
	if (!t.is_infinite(v)) {
	  ll dist = CGAL::squared_distance(u->vertex((i+1)%3)->point(),
					   u->vertex((i+2)%3)->point());
	  dist = std::min(dist, u->info());
	  if (dist > v->info()) {
	    v->info() = dist;
	    Q.push(v);
	  }
	}
      }
    }

    int m; std::cin >> m;

    for (int i = 0; i < m; ++i) {
      int x, y; ll d; std::cin >> x >> y >> d;
      P query(x,y);
      
      Delaunay::Face_handle f = t.locate(query);
      if (CGAL::squared_distance(t.nearest_vertex(query)->point(), query) < d) {
	std::cout << 'n';
      }
      else if (t.is_infinite(f) || f->info() >= 4*d) std::cout << 'y';
      else std::cout << 'n';
    }

    std::cout << std::endl;
  }
  
}


