// STL includes
#include <iostream>
#include <vector>
#include <algorithm>

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/strong_components.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      Graph;
typedef boost::property_map<Graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<Graph>::edge_descriptor            edge;
typedef boost::graph_traits<Graph>::vertex_descriptor          vertex;


#define trace(x)// std::cout << #x << ": " << x << std::endl

void test_case() {
  int n, m, k, T;
  std::cin >> n >> m >> k >> T;

  Graph G(2*n);
  weight_map weights = boost::get(boost::edge_weight, G);
  
  std::vector<bool> network(n,false);
  std::vector<int> net;
  net.reserve(T);
  for (int i = 0; i < T; ++i) {
    int t; std::cin >> t;
    network[t] = true;
    net.push_back(t);
  }

  for (int i = 0; i < m; ++i) {
    int u, v, c; std::cin >> u >> v >> c;
    edge e;
    e = boost::add_edge(v, u, G).first;
    weights[e] = c;
  }

  std::vector<int> c(2*n);
  int num = boost::strong_components
      (G, make_iterator_property_map(c.begin(), get(boost::vertex_index, G), c[0]));

  std::vector<std::vector<int>> connected(num);
  for(int i :net) {
      connected[c[i]].push_back(i);
  }

  
  for(int i = 0; i < connected.size(); ++i){
    if(connected[i].size() > 1){
      for(int x: connected[i]){
        edge e;
        e = boost::add_edge(x,n+i,G).first;
        weights[e] = 0;
        e = boost::add_edge(n+i,x,G).first;
        weights[e] = connected[i].size()-1;
      }
    }
  }
  
  std::vector<int> dist_map(2*n);
  boost::dijkstra_shortest_paths(G, n-1,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G))));

  int res = dist_map[0];
  for (int i = 1; i < k; ++i) {
    res = std::min(res, dist_map[i]);
  }
  
  if (res > 1000000) std::cout << "no\n";
  else std::cout << res << std::endl;  
  
}


int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) test_case();

}
