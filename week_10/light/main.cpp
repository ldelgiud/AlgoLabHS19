#include <iostream>
#include <vector>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef K::Point_2 Point;

#define trace(x) std::cout << #x << " = " << x << std::endl

void test_case() {
  int m, n; std::cin >> m >> n;

  std::vector< std::pair<Point,long> > people;
  people.reserve(m);
  for (int i = 0; i < m; ++i) {
    int x, y, r; std::cin >> x >> y >> r;
    people.push_back({Point(x,y), r});
  }

  long h; std::cin >> h;

  std::vector< Point > lights;
  lights.reserve(n);
  for (int i = 0; i < n; ++i) {
    int x, y; std::cin >> x >> y;
    lights.push_back(Point(x,y));
  }
  
  Triangulation t;
  t.insert(lights.begin(),lights.end());


  bool survivors = false;
  int last_kill = -1;
  std::vector<int> first_hit(m,-1);
  
  for (int i = 0; i < m; ++i) {
    long radius = people[i].second;
    Point position = people[i].first;
    auto closest = t.nearest_vertex(position);

    //if not hit 
    if (CGAL::square(h+radius) <= CGAL::squared_distance(closest->point(), position)) {
      survivors = true;
      continue;
    }

    if (survivors) {
      first_hit[i] = 0;
      continue;
    }
    
    for (int j = 0 ; j < n; ++j) {
      if (CGAL::square(radius+h) >= CGAL::squared_distance(position, lights[j])) {
	first_hit[i] = j;
	last_kill = std::max(last_kill, j);
	break;
      }
    }
  }

  if (survivors) {
    for (int i = 0; i < m; ++i) {
      if (first_hit[i] == -1) std::cout << i << " "; 
    }
  } else {
    for (int i = 0; i < m; ++i) {
      if (first_hit[i] == last_kill) std::cout << i << " ";
    }
  }

  std::cout << std::endl;
}


int main() {
  int t; std::cin >> t;

  while(t--) test_case();

}
