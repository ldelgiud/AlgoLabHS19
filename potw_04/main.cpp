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
typedef std::pair<P,P> Biker;

K::FT speed(const Biker b) {
  return std::abs((b.first.y()-b.second.y())/b.second.x());
}

bool hits(const Biker l, const Biker r) {
  Ray left(P(0,l.first.y()),l.second);
  Ray right(P(0,r.first.y()),r.second);
  return CGAL::do_intersect(left, right);
}
inline bool cmp_biker(const Biker l, const Biker r) {
  return l.first.y() < r.first.y();
}

void test_case() {
  int n; std::cin >> n;

  std::vector<Biker> B;
  B.reserve(n);
  for (int i = 0; i < n; ++i) {
    long y_0, x_1, y_1;
    std::cin >> y_0 >> x_1 >> y_1;
    B.push_back({P(i,y_0),P(x_1,y_1)});
  }
  
  std::sort(B.begin(), B.end(), cmp_biker);
  std::deque<Biker> S;
  int idx = 0;

  while (idx < n) {
    Biker curr = B[idx++];
    while (!S.empty()) {
      Biker opponent = S.front();
      if (hits(curr, opponent)) {
	if (speed(opponent) < speed(curr)) {
	  break;
	} else {
	  S.pop_front();
	}
      } else {
	S.push_front(curr);
	break;
      } 
    } if (S.empty()) S.push_back(curr);
  }

  std::vector<int> survivors;
  for (Biker b : S) {
    survivors.push_back(b.first.x());
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
