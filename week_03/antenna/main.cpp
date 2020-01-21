#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <iostream>

typedef  CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef  CGAL::Min_circle_2_traits_2<K>  Traits;
typedef  CGAL::Min_circle_2<Traits>      Min_circle;
typedef  K::Point_2                      Point;

double ceil_to_double(const K::FT& x)
{
  double a = std::ceil(CGAL::to_double(x));
  while (a-1 > x) a -= 1;
  while (a < x) a += 1;
  return a;
}

void test_case(int n) {

  std::vector<Point> people;
  people.reserve(n);
  
  for (int i = 0; i < n; ++i) {
    long x, y; std::cin >> x >> y;
    Point p(x,y);
    people.push_back(p);
  }

  Min_circle  mc(people.begin(), people.end(), true);
  Traits::Circle c = mc.circle();
  std::cout << ceil_to_double(CGAL::sqrt(c.squared_radius()))<< std::endl;
  
}

int main() {
  int n; std::cin >> n;
  std::cout << std::fixed << std::setprecision(0);
  while(n) {
    test_case(n);
    std::cin >> n;
  }
}
