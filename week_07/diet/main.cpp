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
typedef CGAL::Quotient<ET> SolutionType;
#define trace(x)// std::cout << #x << ": " << x << std::endl

double floor_to_double(const SolutionType& x){
  double a = std::floor(CGAL::to_double(x));
  while(a > x) --a;
  while(a + 1 <= x) ++a;
  return a;
}

int main() {
  int n,m;
  
  while(true) {
    std::cin >> n >> m;
    trace(n);
    trace(m);
    if (n==0 && m==0) break;
    
    // create an LP with Ax <= b, lower bound 0 and no upper bounds
    Program lp (CGAL::SMALLER, true, 0, false, 0);

    //<min,max>
    std::vector<std::pair<int,int>> Recommended;
    Recommended.reserve(n);
    for (int i = 0; i < n; ++i) {
      int min, max;
      std::cin >> min >> max;
      Recommended.push_back(std::make_pair(min,max));
    }

    for (int i = 0; i < m; ++i) {
      int cost; std::cin >> cost;
      lp.set_c(i,cost);
      for (int j = 0; j < n; ++j) {
	int tmp; std::cin >> tmp;	
	lp.set_a(i, j, tmp);
	lp.set_a(i, n+j,-tmp);
      }
    }

    for (int i = 0; i < n; ++i) {
      lp.set_b(i  , Recommended[i].second);
      lp.set_b(n+i, -Recommended[i].first);
    }
    
    // solve the program, using ET as the exact type
    Solution s = CGAL::solve_linear_program(lp, ET());
    
    if (s.is_infeasible()) {
      std::cout << "No such diet.\n";
    } else {
      std::cout << floor_to_double(s.objective_value()) << std::endl;
    }
  }  
}
