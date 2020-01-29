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

#define trace(x)// std::cout << #x << " = " << x << std::endl
#define step(x) //std::cout << "STEP: " << x << std::endl

void test_case() {
  int n, s; std::cin >> n >> s;
  weighted_graph G(n);
  weight_map weights = boost::get(boost::edge_weight, G);
  --s;

  //READ
  for (int j = 0; j < n-1; ++j) {
    for (int k = j+1; k < n; ++k) {
      int c;
      std::cin >> c;
      edge_desc e = boost::add_edge(j, k, G).first;
      weights[e]=c;
    }
  }

  //FIND MST (with Prim)
  std::vector<vertex_desc> p(n);
  boost::prim_minimum_spanning_tree(G, &p[0]);

  long best = 1 << 29;
  for (int i = 0; i < n; ++i) {
    if (p[i] == i) continue;
    edge_desc e = boost::edge(i, p[i], G).first;
    int e_w = weights[e];
    weights[e] = 1 << 29;

    std::vector<vertex_desc> p2(n);
    boost::prim_minimum_spanning_tree(G, &p2[0]);//, boost::root_vertex(s));
    long sum = 0;
    for (int j = 0; j < n; ++j) {
      if (p2[j] == j) continue;
      sum += weights[boost::edge(j, p2[j], G).first];
    }
    best = std::min(best, sum);
    weights[e] = e_w;
  }


  std::cout << best << std::endl;
}


int main() {
  std::ios_base::sync_with_stdio(false);
  int t;
  std::cin >> t;
  while(t--) test_case();
}
