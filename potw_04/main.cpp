#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Ray_2.h>
typedef CGAL::Exact_predicates_inexact_constructions_kernel   K;
typedef K::Ray_2 Ray;
typedef K::Point_2 Point;

void test_case() {
  int n; std::cin >> n;
  //biker, active
  std::vector<std::pair<Ray, int>> bikers;
  bikers.reserve(n);
    
  for (int i = 0; i < n; ++i) {
    long y_0, x_1, y_1;
    std::cin >> y_0 >> x_1 >> y_1;
    bikers.push_back(std::make_pair(Ray(Point(0,y_0), Point(x_1, y_1)),i));
  }
  
  std::sort(bikers.begin(), bikers.end(), [](std::pair <Ray,int> a, std::pair<Ray,int>b) {

      Ray a1 = a.first;
      Ray b1 = b.first;
      double angle_a = std::atan(CGAL::to_double(
			       a1.point(1).x()/(a1.point(1).y()-a1.source().y())));
      double angle_b = std::atan(CGAL::to_double(
			       b1.point(1).x()/(b1.point(1).y()-b1.source().y())));

      if (angle_a > std::atan(1)*4) angle_a -= std::atan(1)*4;
      if (angle_b > std::atan(1)*4) angle_b -= std::atan(1)*4;
      
      if (angle_a < angle_b) {
	return false;
      } else if
	  (angle_a  == angle_b) {
	return !(a1.source().y() < b1.source().y()); 
      } else return true;
    });

  std::vector<bool> alive(n, true);
  for (int i = 0; i < n; ++i) {
    if (alive[i]) {
      for (int j = i+1; j < n; ++j) {
	if (alive[j]) {
	  if (CGAL::do_intersect(bikers[i].first,bikers[j].first)) alive[j] = false;
	  
	}
      }
    }
  }

  
  int cnt = -1;
  std::vector<int> res;
  for (bool i: alive) {
    ++cnt;
    if (i) res.push_back(bikers[cnt].second);
  }

  std::sort(res.begin(), res.end());

  for (int i: res) std::cout << i << ' ';
  std::cout << std::endl;
}


int main() {
  std::ios::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) test_case();
  
}
