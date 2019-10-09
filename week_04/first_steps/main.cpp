// STL includes
#include <iostream>
#include <vector>

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property,                         // no vertex property
  boost::property<boost::edge_weight_t, int>  // interior edge weight property
> weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

void test_case()
{
  int n,m;
  std::cin >> n >> m;
  weighted_graph G(n);
  weight_map weights = boost::get(boost::edge_weight, G);

  for (int i = 0; i < m; ++i) {
    int u, v, w;
    std::cin >> u >> v >> w;
    edge_desc e = boost::add_edge(u, v, G).first;
    weights[e]= w;
  }

  std::vector<edge_desc> mst;    // vector to store MST edges (not a property map!)

  boost::kruskal_minimum_spanning_tree(G, std::back_inserter(mst));
  int sum = 0;

  for (auto it = mst.begin(); it != mst.end(); ++it) {
    sum += weights[*it];
  }

  std::vector<int>         dist_map(n);
  std::vector<vertex_desc> pred_map(n);

    boost::dijkstra_shortest_paths(G, 0,
      boost::distance_map(boost::make_iterator_property_map(
        dist_map.begin(), boost::get(boost::vertex_index, G)))
      .predecessor_map(boost::make_iterator_property_map(
        pred_map.begin(), boost::get(boost::vertex_index, G))));

  int max_dist = 0;
  for (int dist: dist_map) {
    max_dist = std::max(dist, max_dist);
  }

  std::cout << sum << ' ' << max_dist << std::endl;

}

int main()
{
  int t; std::cin >> t;
  while(t--) test_case();
}
