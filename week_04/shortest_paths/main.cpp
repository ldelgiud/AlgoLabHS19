#include <iostream>
#include <vector>

#include <boost/config.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/johnson_all_pairs_shortest.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

void test_case() {
  int n, m, q;
  std::cin >> n >> m >> q;

  weighted_graph G(n);
  weight_map weights = boost::get(boost::edge_weight, G);

  for (int i = 0; i < n; ++i) {
    int lon, lat;
    std::cin >> lon >> lat;
  }

  for (int i = 0; i < m; ++i) {
    int a, b, c;
    std::cin >> a >> b >> c;
    edge_desc e; bool success;
    boost::tie(e, success) = boost::add_edge(a, b, G);
    if (success) weights[e] = c;
  }

  for (int i = 0; i < q; ++i) {
    std::vector<int> dist_map(n);
    int s, t; std::cin >> s >> t;
    boost::dijkstra_shortest_paths(G, s,
      boost::distance_map(boost::make_iterator_property_map(
        dist_map.begin(), boost::get(boost::vertex_index, G))));

    if(dist_map[t] == std::numeric_limits<int>::max()){
      std::cout << "unreachable" << std::endl;
    } else {
      std::cout << dist_map[t] << std::endl;
    }
  }

}




int main() {
  test_case();
}
