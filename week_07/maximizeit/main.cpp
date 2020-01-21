#include <iostream>

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

double ceil_to_double(const SolutionType& x){
  double a = std::ceil(CGAL::to_double(x));
  while(a < x) ++a;
  while(a - 1 >= x) --a;
  if(abs(a) == 0) a = 0;
  return a;
}

double floor_to_double(const SolutionType& x){
  double a = std::floor(CGAL::to_double(x));
  while(a > x) --a;
  while(a + 1 <= x) ++a;
  return a;
}

void test_case() {
 
}


int main() {
  while(true) {
    int q, a, b;
    std::cin >> q;
    if (q == 0) break;
    std::cin >> a >> b;
    Program lp (CGAL::SMALLER, false, 0, false, 0);
    const int X = 0;
    const int Y = 1;
    const int Z = 2;
    if (q==1) {
      lp.set_l(X, true, 0); // x >= 0
      lp.set_l(Y, true, 0); // y >= 0
    
      lp.set_a(X, 0, 1); lp.set_a(Y, 0, 1); lp.set_b(0, 4); // x + y <= 4
      lp.set_a(X, 1, 4); lp.set_a(Y, 1, 2); lp.set_b(1, a*b); // 4x + 2y <= ab
      lp.set_a(X, 2,-1); lp.set_a(Y, 2, 1); lp.set_b(2, 1); // -x + y <= 1

      lp.set_c(X, a);
      lp.set_c(Y, -b);
    } else {
      lp.set_u(X, true, 0); // x >= 0
      lp.set_u(Y, true, 0); // y >= 0
      lp.set_u(Z, true, 0); // z >= 0

      lp.set_a(X, 0,-1); lp.set_a(Y, 0,-1);                    lp.set_b(0, 4); // -x + -y <= 4
      lp.set_a(X, 1,-4); lp.set_a(Y, 1,-2); lp.set_a(Z, 1,-1); lp.set_b(1, a*b);// -4x -2y -z<= ab
      lp.set_a(X, 2, 1); lp.set_a(Y, 2, -1); lp.set_b(2, 1); // x - y <= 1

      lp.set_c(X, a);
      lp.set_c(Y, b);
      lp.set_c(Z, 1);
    }

    //add if unb
    Solution s = CGAL::solve_linear_program(lp, ET());
    if (s.is_infeasible()) {
      std::cout << "no\n";
    } else if (s.is_unbounded()) {
      std::cout << "unbounded\n";
    } else {
      if (q==1) {
	std::cout << floor_to_double(-s.objective_value()) << std::endl;
      } else {
	std::cout << ceil_to_double(s.objective_value()) << std::endl;
      }
      
    }
  }

}
