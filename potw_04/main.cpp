#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Ray_2.h>
typedef CGAL::Exact_predicates_inexact_constructions_kernel   K;
typedef K::Ray_2 Ray;
typedef K::Point_2 P;
// {(idx, y_0), (x_1, y_1)}
typedef std::pair<Ray,int> Biker;

K::FT speed(const Biker r) {
  return r.first.direction().dy() / r.first.direction().dx();
}
inline bool cmp_biker(const Biker l, const Biker r) {
  return l.first.source().y() < r.first.source().y();
}

void test_case() {
  int n; std::cin >> n;

  std::vector<Biker> B;
  B.reserve(n);
  for (int i = 0; i < n; ++i) {
    K::FT y_0, x_1, y_1;
    std::cin >> y_0 >> x_1 >> y_1;
    B.push_back({Ray(P(0,y_0),P(x_1,y_1)),i});
  }
  
  std::sort(B.begin(), B.end(), cmp_biker);
  std::deque<Biker> S;
  S.push_front(B[0]);
  int idx = 1;

  while (idx < n) {
    Biker curr = B[idx++];

    while (!S.empty()) {
      Biker opponent = S.front();
      if (CGAL::do_intersect(curr.first, opponent.first)) {
	if (speed(curr) + speed(opponent) > 0) {
	  S.pop_front();
	} else break;
      } else {
	S.push_front(curr);
	break;
      } 
    } if (S.empty()) S.push_back(curr);
  }

  std::vector<int> survivors;
  for (Biker b : S) {
    survivors.push_back(b.second);
  }

  std::sort(survivors.begin(), survivors.end());
  for (int i : survivors) {
    std::cout << i << ' ';
  }
  std::cout << std::endl;
}


int main() {
  std::ios::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) test_case(); 
}
