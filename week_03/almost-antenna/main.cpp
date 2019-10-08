#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <vector>

// typedefs
typedef  CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef  CGAL::Min_circle_2_traits_2<K>  Traits;
typedef  CGAL::Min_circle_2<Traits>      Min_circle;
typedef  K::Point_2                      Point;

double ceil_to_double(const K::FT& x)
{
  double a = std::ceil(CGAL::to_double(x));
  while (a-1 > x) --a;
  while (a < x) ++a;
  return a;
}

int main()
{
  std::cout << std::fixed << std::setprecision(0);
  std::ios::sync_with_stdio(false);
  int n;
  std::vector<Point> points;
  std::vector<Point> new_points;
  
  while (true) {
    
    std::cin >> n;
    if (!n) break;
    
    points.clear();
    points.reserve(n);
    new_points.clear();

    for (int i = 0; i < n; ++i) {
      long x, y;
      std::cin >> x >> y;
      points.push_back(Point(x,y));
    }

    Min_circle mc(points.begin(), points.end(), true);
    
    for (Point p: points) {
      if (std::find(mc.support_points_begin(), mc.support_points_end(), p)
	  == mc.support_points_end()) {
	new_points.push_back(p);
      }   
    }
    
    K::FT best_sqrd_rad(std::numeric_limits<double>::max());
    
    for (int i = 0; i < mc.number_of_support_points(); ++i) {
      Min_circle mc2(new_points.begin(), new_points.end(), true);
      for (int j = 0; j < mc.number_of_support_points(); ++j) {
	if (j!= i) mc2.insert(mc.support_point(j));     
      }
      Traits::Circle c = mc2.circle();
      if (best_sqrd_rad > c.squared_radius()) best_sqrd_rad = c.squared_radius();
    }
    std::cout << ceil_to_double(CGAL::sqrt(best_sqrd_rad)) << std::endl;

  } 
  
}
