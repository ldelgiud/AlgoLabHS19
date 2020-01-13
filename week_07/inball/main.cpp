#include <iostream>
#include <vector>
#include <cmath>

// example: how to solve a simple explicit LP
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

// choose input type (input coefficients must fit)
typedef int IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET;
typedef CGAL::Quotient<ET> SolutionType;
// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

double floor_to_double(const SolutionType& x){
  double a = std::floor(CGAL::to_double(x));
  while(a > x) --a;
  while(a + 1 <= x) ++a;
  return a;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int n,d;
  
  while(true) {
    std::cin >> n;
    if (!n) break;
    std::cin >> d;
    
    Program lp (CGAL::SMALLER, false, 0, false, 0); 
    lp.set_a(0, 0, -1);
    lp.set_b(0, 0);
    
    for (int i = 1; i <= n; ++i) {
      int len = 0;
      for (int j = 1; j <= d; ++j) {
	int a; std::cin >> a;
	lp.set_a(j, i,  a);
	len += a*a;
      }
     
      lp.set_a(0, i, std::sqrt(len));
      int b; std::cin >> b;
      lp.set_b(i, b);
    }

    lp.set_c(0,-1);


    Solution s = CGAL::solve_linear_program(lp, ET());
    assert(s.solves_linear_program(lp));
    if(s.is_infeasible()) {
      std::cout << "none\n";
    } else if (s.is_unbounded()) {
      std::cout << "inf\n";
    } else {
      std::cout << floor_to_double(-s.objective_value()) << std::endl; 	  
    }
    // output solution
    
  }
}
