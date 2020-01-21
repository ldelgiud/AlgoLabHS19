#include <iostream>
#include <vector>

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

void test_case() {

  int k; std::cin >> k; int n = k*(k+1)/2;
  //std::vector<std::vector<int>> weights(k);
  std::vector<int> weights;
  weights.reserve(n);

  weighted_graph G(k*(k+1)/2);
  //weighted_graph G2(k*(k+1)/2);
  weight_map weight_map = boost::get(boost::edge_weight, G);

  for (int i = 0; i < k; ++i) {
    for (int j = 0; j <= i; ++j) {
      int v; std::cin >> v;
      //weights[i].push_back(v);
      weights.push_back(v);
    }
  }
  int idx = 0;
  for (int i = 0; i < k; ++i) {
    for (int j = 0; j <= i; ++j) {

      //Vertical Edges
      if (i < k-1) {
	edge_desc e;
	e = boost::add_edge(idx, idx+i+1, G).first; weight_map[e]=weights[idx+i+1];
	e = boost::add_edge(idx, idx+i+2, G).first; weight_map[e]=weights[idx+i+2];

	e = boost::add_edge(idx+i+1, idx, G).first; weight_map[e]=weights[idx];
	e = boost::add_edge(idx+i+2, idx, G).first; weight_map[e]=weights[idx];
      }
      //Horizontal Edges
      if (j < i) {
	edge_desc e;
	e = boost::add_edge(idx, idx+1, G).first; weight_map[e]=weights[idx+1];
	
	e = boost::add_edge(idx+1, idx, G).first; weight_map[e]=weights[idx];
      }
      ++idx;
    }
  }

  int top = 0, left = k*(k-1)/2, right = (k*(k+1)/2)-1;

  std::vector<int> dist_map1(n);
  boost::dijkstra_shortest_paths(G, top,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map1.begin(), boost::get(boost::vertex_index, G))));
  std::vector<int> dist_map2(n);
  boost::dijkstra_shortest_paths(G, left,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map2.begin(), boost::get(boost::vertex_index, G))));
  std::vector<int> dist_map3(n);
  boost::dijkstra_shortest_paths(G, right,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map3.begin(), boost::get(boost::vertex_index, G))));

  
  int best = 1 << 27;
  for (int i = 0; i < n; ++i) {
    best = std::min(best,
		    dist_map1[i]+dist_map2[i]+dist_map3[i]-2*weights[i]);
  }

  
  std::cout << best << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) test_case();

}

