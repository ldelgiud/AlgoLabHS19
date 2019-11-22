#include <iostream>
#include <vector>
#include <utility>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
// choose input type (input coefficients must fit)
typedef int IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
typedef CGAL::Quotient<ET> SolT;
typedef std::pair<int,int> Nail;

#define trace(x) //std::cout << #x << ": " << x << std::endl;

double ceil_to_double(const SolT& x) {
  double a = std::ceil(CGAL::to_double(x));
  while (a < x) a += 1;
  while (a-1 >= x) a -= 1;
  return a;
}


const int INF = std::numeric_limits<int>::max();
void test_case() {
  int n, m, h, w;
  std::cin >> n >> m >> h >> w;
  
  Program lp (CGAL::SMALLER, true, 1, false, 0);

  std::vector<Nail> new_nails;
  new_nails.reserve(n);
  std::vector<Nail> old_nails;
  old_nails.reserve(m);
  
  for (int i = 0; i < n; ++i) {
    int x, y; std::cin >> x >> y;
    new_nails.push_back(Nail(x,y));
  }

  for (int i = 0; i < m; ++i) {
    int x, y; std::cin >> x >> y;
    old_nails.push_back(Nail(x,y));
  }

  for (int i = 0; i < n; ++i) {
    lp.set_c(i, -2*(w+h));
  }
  
  for (int i = 0; i < n; ++i) {
    if (m == 0) break;
    int min_x = INF, min_y = INF;
    for (int j = 0; j < m; ++j) {
      int d_x = std::abs(new_nails[i].first - old_nails[j].first) - w;
      int d_y = std::abs(new_nails[i].second - old_nails[j].second) -h;
      if (d_x > d_y){
	if (d_x < min_x) min_x = d_x;
      } 
      else {
	if (d_y < min_y) min_y = d_y;
      }
    }
    if (min_x*h < min_y*w) {
      lp.set_a(i, i, w); lp.set_b(i, 2*min_x-w); // a_i*w <= 2d_x - w
    } else {
      lp.set_a(i, i, h); lp.set_b(i, 2*min_y-h); // a_i*h<= 2d_y- h
    }
  }

  int cnt = n;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < i; ++j) {
      int d_x = std::abs(new_nails[i].first - new_nails[j].first);
      int d_y = std::abs(new_nails[i].second - new_nails[j].second);
      trace(d_x);
      trace(d_y);
      if (d_x*h > d_y*w) {
	lp.set_a(i, cnt, w);
	lp.set_a(j, cnt, w);
	lp.set_b(   cnt, 2*d_x); // a_j*w + a_i*w <= 2*d_x
	trace(w);
      } else {
	lp.set_a(i, cnt, h);
	lp.set_a(j, cnt, h);
	lp.set_b(   cnt, 2*d_y); // a_j*w + a_i*h <= 2*d_y
	trace(h);
      }
      ++cnt;
    }
  }

  Solution s = CGAL::solve_linear_program(lp, ET());
  //std::cout << s << std::endl;
  std::cout << ceil_to_double(-s.objective_value()) << std::endl;
  
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout << std::fixed << std::setprecision(0);
  int t; std::cin >> t;
  while(t--) test_case();
  
}
