#include <iostream>
#include <string>
#include <map>
#include <set>
#include <utility>
#include <algorithm>

#include <boost/graph/adjacency_list.hpp>
#include <cassert>
#include <boost/graph/max_cardinality_matching.hpp>


typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> Graph;
typedef boost::graph_traits<Graph>::edge_descriptor            Edge;
typedef boost::graph_traits<Graph>::vertex_descriptor          Vertex;
typedef std::vector<std::string> Interests;
#define trace(x) // std::cout << #x << " = " << x << std::endl

int common_interests(const Interests l, const Interests r) {

  int i = 0, j = 0, res = 0;

  while (i < l.size() && j < r.size()) {
    if (l[i] == r[j]) {
      ++res;
      ++i;
      ++j;
    } else if (l[i] < r[j]) ++i;
    else ++j;
  }

  return res;
}

void test_case() {
  int n, c, f;
  std::cin >> n >> c >> f;

  std::vector<Interests> students(n);
 
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < c; ++j) {
      std::string str; std::cin >> str;
      students[i].push_back(str);
    }
    std::sort(students[i].begin(), students[i].end());
  }

  Graph G(n);

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < i; ++j) {
      if (common_interests(students[i], students[j]) > f) {
	boost::add_edge(i, j, G);
      }
    }
  }

  std::vector<Vertex> matemap(n);

   boost::edmonds_maximum_cardinality_matching(G,
       boost::make_iterator_property_map(matemap.begin(),
       boost::get(boost::vertex_index,G)));

   int matchsize = boost::matching_size(G,
       boost::make_iterator_property_map(matemap.begin(),
       boost::get(boost::vertex_index,G)));

   if(matchsize == n/2)
     std::cout << "not optimal" << std::endl;
   else
     std::cout << "optimal" << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) test_case();
}
