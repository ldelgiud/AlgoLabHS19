#include <iostream>
#include <vector>

// example: decide whether two point sets R and B can be separated by a nonvertical line
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

// choose input type (input coefficients must fit)
typedef CGAL::Gmpz IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

#define trace(x)// std::cerr << #x << " = " << x << std::endl

struct P {
  IT x, y, z; 
};

P pow(std::vector<std::vector<std::pair<bool,P>>>& pows, int i, int power){
  if (power == 0) return pows[i][0].second;
  if (pows[i][power].first) return pows[i][power].second;
  P prev = pow(pows, i, power-1);
  prev.x *= pows[i][1].second.x;
  prev.y *= pows[i][1].second.y;
  prev.z *= pows[i][1].second.z;
  pows[i][power].second = prev;
  pows[i][power].first = true;
  return prev;
}


void test_case() {
  int h, t; std::cin >> h >> t;
  Program lp (CGAL::SMALLER, false, 0, false, 0);
  std::pair<bool, P> init = {false,{1,1,1}};
  std::vector<std::vector<std::pair<bool,P>>> powH(h,std::vector<std::pair<bool,P>>(31,init));
  std::vector<std::vector<std::pair<bool,P>>> powT(t,std::vector<std::pair<bool,P>>(31,init));
  std::vector<P> healthy;

  for (int i = 0; i < h; ++i) {
    IT x, y, z; std::cin >> x >> y >> z;
    healthy.push_back({x,y,z});
    powH[i][1].second = {x,y,z};
    powH[i][1].first = true;
  }
  std::vector<P> sick;
  for (int i = 0; i < t; ++i) {
    IT x, y, z; std::cin >> x >> y >> z;
    sick.push_back({x,y,z});
    powT[i][1].second = {x,y,z};
    powT[i][1].first = true;
  }

  for (int d = 0; d <= 30; ++d) {
    Program lp (CGAL::SMALLER,false,0,false,0);

    for (int i = 0; i < h; ++i) {
      lp.set_b(i, -1);
      int cnt = 0;
      for (int x = 0; x <= d; ++x) {
	for (int y = 0; y <= d; ++y) {
	  for (int z = 0; z <= d; ++z) {
	    if (x+y+z <= d) {
	      lp.set_a(cnt++, i, pow(powH, i, x).x*pow(powH, i, y).y*pow(powH, i, z).z);
	    }
	  }
	}
      }
    }
    for (int i = 0; i < t; ++i) {
      lp.set_b(h+i, -1);
      int cnt = 0;
      for (int x = 0; x <= d; ++x) {
	for (int y = 0; y <= d; ++y) {
	  for (int z = 0; z <= d; ++z) {
	    if (x+y+z <= d) {
	      lp.set_a(cnt++, h+i, -pow(powT, i, x).x*pow(powT, i, y).y*pow(powT, i, z).z);
	    }
	  }
	}
      }
    }

    CGAL::Quadratic_program_options options;
    options.set_pricing_strategy(CGAL::QP_BLAND);
    Solution s = CGAL::solve_linear_program(lp,ET(),options);
    if (!s.is_infeasible()) {
      std::cout << d << std::endl;
      return;
    }
  }
  std::cout << "Impossible!\n";
}


int main() {
  int N; std::cin >> N;
  while(N--) test_case();
}
