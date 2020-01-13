// STL includes
#include <iostream>
#include <vector>

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

void test_case() {
  int n, s; std::cin >> n >> s;
  weighted_graph G(n);
  weight_map weights = boost::get(boost::edge_weight, G);

  //READ
  for (int j = 1; j < n; ++j) {
    for (int k = j; k < n; ++k) {
      int c;
      std::cin >> c;
      edge_desc e = boost::add_edge(j, k, G).first;
      weights[e]=c;
    }
  }

  //FIND MST (with Prim)
  std::vector<vertex_desc> prim_pred_map(n);
  boost::prim_minimum_spanning_tree(G, &prim_pred_map[0]);

}


int main() {
  int t;
  std::cin >> t;

  while(t--) test_case();
}
