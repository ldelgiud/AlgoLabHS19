#include <iostream>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/biconnected_components.hpp>

namespace boost
{
  struct edge_component_t
  {
    enum
    { num = 555 };
    typedef edge_property_tag kind;
  }
  edge_component;
}

typedef boost::adjacency_list <boost::vecS, boost::vecS, boost::undirectedS,
			boost::no_property,
			boost::property <
			  boost::edge_component_t,
			  std::size_t > > Graph;

void test_case() {
  int n, m; std::cin >> n >> m;
  Graph G(n);

  for (int i = 0; i < m; ++i) {
    int u, v; std::cin >> u >> v;
    boost::add_edge(u, v, G);
  }

  auto comp = boost::get(boost::edge_component, G);
  std::size_t num_comps = biconnected_components(G, comp);
  std::vector<int> num_edges(num_comps, 0);
  for (auto ei = boost::edges(G).first; ei != boost::edges(G).second; ++ei) {
    ++num_edges[comp[*ei]];
  }

  std::vector<std::pair<int,int>> bridges;
  for (auto ei = boost::edges(G).first; ei != boost::edges(G).second; ++ei) {
    if (num_edges[comp[*ei]] == 1) {
      int src = std::min(boost::source(*ei, G), boost::target(*ei, G));
      int trg = std::max(boost::source(*ei, G), boost::target(*ei, G));
      bridges.push_back({src, trg});
    } 
  }
  std::sort(bridges.begin(), bridges.end());
  std::cout << bridges.size() << std::endl;

  for (auto tmp : bridges) std::cout << tmp.first << ' ' << tmp.second << std::endl;

  
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) test_case();
}
