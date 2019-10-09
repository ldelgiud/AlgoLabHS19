#include <boost/config.hpp>
#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>



typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex;


void test_case() {
  int n, e, s, a, b;
  std::cin >> n >> e >> s >> a >> b;
  std::vector<weighted_graph> graphs(s, weighted_graph(n));
  std::vector<weight_map> maps(s);
  for (int i = 0; i < s; ++i) {
    maps[i] = boost::get(boost::edge_weight, graphs[i]);
  }

  for (int i = 0; i < e; ++i) {
    int u, v;
    std::cin >> u >> v;

    for (int j = 0; j < s; ++j) {
      int h; std::cin >> h;
      edge e = boost::add_edge(u, v, graphs[j]).first;
      maps[j][e] = h;
    }
  }

  std::vector<int> hives(s);
  for (int i = 0; i < s; ++i) {
    int h; std::cin >> h;
    hives[i] = h;
  }

}


int main() {
  int t; std::cin >> t;
  while(t--) test_case();

}
