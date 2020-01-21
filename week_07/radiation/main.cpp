#include <iostream>
#include <vector>

// example: decide whether two point sets R and B can be separated by a nonvertical line
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



void test_case() {
  int h, t; std::cin >> h >> t;
  Program lp (CGAL::SMALLER, false, 0, false, 0);

  
  for (int i = 0; i < h; ++i) {
    int x, y, z; std::cin >> x >> y >> z;
    
  }

  for (int i = 0; i < t; ++j) {
    int x, y, z; std::cin >> x >> y >> z;

  }

}


int main() {
  int N; std::cin >> N;
  while(N--) test_case();
}
