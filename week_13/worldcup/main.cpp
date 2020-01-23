#include <iostream>
#include <vector>
#include <iomanip>
// example: how to solve a simple explicit LP
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
// choose input type (input coefficients must fit)
typedef int IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
typedef CGAL::Quotient<ET> Sol_t;

typedef CGAL::Exact_predicates_inexact_constructions_kernel    K;
typedef CGAL::Triangulation_vertex_base_with_info_2<long,K>    Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;

typedef K::Point_2 Point;

double floor_to_double(const Sol_t &x) {
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

void test_case() {
  int n, m, c; std::cin >> n >> m >> c;

  Program lp (CGAL::SMALLER, true, 0, false, 0); 

  std::vector<int> alcohol;
  std::vector<std::pair<Point,long>> stadium;
  std::vector<std::pair<Point,long>> warehouse;
  
  for (int i = 0; i < n; ++i) {
    int x, y, s, a; std::cin >> x >> y >> s >> a;
    alcohol.push_back(a);
    warehouse.push_back({Point(x,y),i});
    lp.set_b(i, s);
    for (int j = 0; j < m; ++j) {
      lp.set_a(i*m+j, i, 1);
    }
  }

  for (int i = 0; i < m; ++i) {
    int x, y, d, u; std::cin >> x >> y >> d >> u;
    stadium.push_back({Point(x,y),i});
    lp.set_b(n+i, d);
    lp.set_b(n+m+i, -d);
    for (int j = 0; j < n; ++j) {
      lp.set_a(j*m+i, n+i, 1);
      lp.set_a(j*m+i, n+m+i, -1);
    }
    lp.set_b(n+2*m+i, 100*u);
    for (int j = 0; j < n; ++j) {
      lp.set_a(j*m+i, n+2*m+i, alcohol[j]);
    }
  }

  int cnt = 0;
  for (int i = 0; i < n; ++i) {

    for (int j = 0; j < m; ++j) {
      int w; std::cin >> w;
      lp.set_c(cnt, -w);
      ++cnt;
    }
  }

  std::vector<std::pair<Point, long>> circle;
  circle.reserve(c);
  for (int i = 0; i < c; ++i) {
    int x, y;
    long r; std::cin >> x >> y >> r;
    circle.push_back({Point(x,y), r*r});
  }

  if (c > 0) {
    Delaunay t;
    t.insert(circle.begin(), circle.end());
    
    std::set<std::pair<Point, long>> active;
    for (int i = 0; i < n; ++i) {
      auto nearest = t.nearest_vertex(warehouse[i].first);
      if (CGAL::squared_distance(nearest->point(), warehouse[i].first) < nearest->info()) {

      }

    }
  }
  Solution s = CGAL::solve_linear_program(lp, ET());
  assert(s.solves_linear_program(lp));
  
  // output solution
  if(s.is_infeasible()) std::cout << "RIOT!\n";
  else std::cout << floor_to_double(-s.objective_value()) << std::endl; 
}


int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout << std::fixed << std::setprecision(0);
  int t; std::cin >> t;
  while (t--) test_case();
}
