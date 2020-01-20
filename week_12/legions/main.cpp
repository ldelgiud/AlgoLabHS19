#include <iostream>
#include <cmath>

// example: how to solve a simple explicit LP
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

// choose input type (input coefficients must fit)
typedef int IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

#define trace(x) //std::cout << #x << " = " << x << std::endl
#define step(x) //std::cout << "Step: " << x << std::endl

double floor_to_double(const CGAL::Quotient<CGAL::Gmpz>& x)
{
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

void test_case() {
  int x, y, n; std::cin >> x >> y >> n;
  const int R = 0, X = 1, Y = 2;
  Program lp (CGAL::SMALLER, false, 0, false, 0); 


  lp.set_a(R, 0, -1);
  lp.set_b(   0, 0);

  for (int i = 1; i <= n; ++i) {
    int a, b, c, v; std::cin >> a >> b >> c >> v;
    int len = std::sqrt(a*a+b*b);
    trace(a*x+b*y+c);
    if (a*x+b*y+c > 0) {
      step("left");
      lp.set_a(X, i, -a);
      lp.set_a(Y, i, -b);
      lp.set_a(R, i, len);
      lp.set_b(   i, c);
    } else {
      step("right");
      lp.set_a(X, i, a);
      lp.set_a(Y, i, b);
      lp.set_a(R, i, -len);
      lp.set_b(   i, -c);
    }
  }

  lp.set_c(R, -1);
  lp.set_c(X, 0);
  lp.set_c(Y, 0);


  Solution s = CGAL::solve_linear_program(lp, ET());
  assert(s.solves_linear_program(lp));
  std::cout << floor_to_double(-s.objective_value())<< std::endl;
}


int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout << std::fixed << std::setprecision(0);
  int t; std::cin >> t;
  while(t--) test_case();

}
