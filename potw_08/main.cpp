#include <iostream>
#include <vector>
#include <utility>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpq ET;

// program and solution types
typedef CGAL::Quadratic_program<ET> Program;
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

  //NEW-OLD Conflicts
  for (int i = 0; i < n; ++i) {
    ET best = 1<<29;

    for (int j = 0; j < m; ++j) {
      ET d_x = std::abs(new_nails[i].first - old_nails[j].first);
      ET d_y = std::abs(new_nails[i].second - old_nails[j].second);
      best = std::min(2*std::max(d_x/w, d_y/h)-1, best);
      
    }
    lp.set_a(i, i, 1); lp.set_b(i, best);
    
  }

  //NEW-NEW Conflicts
  int cnt = n;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < i; ++j) {
      ET d_x = std::abs(new_nails[i].first - new_nails[j].first);
      ET d_y = std::abs(new_nails[i].second - new_nails[j].second);
      
      lp.set_a(i, cnt, 1);
      lp.set_a(j, cnt, 1);
      lp.set_b(   cnt, 2*std::max(d_x/w, d_y/h)); // a_j + a_i <= 2*max{d_x/w, d_y/h}
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
