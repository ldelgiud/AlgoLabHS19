#include <boost/config.hpp>
#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>



typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex;

#define trace(x) std::cout << #x << " = " << x << std::endl


void test_case() {
  int n, e, s, a, b;
  std::cin >> n >> e >> s >> a >> b;
  std::vector<weighted_graph> graphs(s, weighted_graph(n));
  std::vector<weight_map> maps(s);

  weighted_graph G(n);
  weight_map weights  = boost::get(boost::edge_weight, G);

  for (int i = 0; i < s; ++i) {
    maps[i] = boost::get(boost::edge_weight, graphs[i]);
  }

  for (int i = 0; i < e; ++i) {
    int u, v;
    std::cin >> u >> v;
    edge e; bool success;
    tie(e,success) = add_edge(u,v,G);
    weights[e] = std::numeric_limits<int>::max();

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



  for (int i = 0; i < s; ++i) {
    std::vector<vertex> mst(n);

    prim_minimum_spanning_tree(graphs[i],
        make_iterator_property_map(mst.begin(),
                                   get(boost::vertex_index,graphs[i])),
        boost::root_vertex(hives[i]));

    for(int j=0;j<n;j++){
      if(mst[j] != j){
        edge e; bool success;
        tie(e,success) = boost::edge(j,mst[j],graphs[i]);

        // find the same edge in the global network
        vertex u = boost::source(e,graphs[i]);
        vertex v = boost::target(e,graphs[i]);
        edge e_ = boost::edge(u,v,G).first;
        weights[e_] = std::min(weights[e_],maps[i][e]);
      }
    }
  }



  std::vector<int> dist_map(n);

  boost::dijkstra_shortest_paths(G, a,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G))));


  std::cout << dist_map[b] << std::endl;


}


int main() {
  int t; std::cin >> t;
  while(t--) test_case();

}
