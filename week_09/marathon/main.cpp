// ALGOLAB BGL Tutorial 3
// Code demonstrating 
// - MinCostMaxFlow with arbitrary edge costs using cycle_canceling
// - MinCostMaxFlow with non-negative edge costs using successive_shortest_path_nonnegative_weights

// Includes
// ========
#include <iostream>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

// Graph Type with nested interior edge properties for Cost Flow Algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > graph; // new! weightmap corresponds to costs

typedef boost::graph_traits<graph>::edge_descriptor             edge;
typedef boost::graph_traits<graph>::edge_iterator           edge_it; // Iterator

// Custom edge adder class, highly recommended
class edge_adder {
  graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}

  void add_edge(int from, int to, long capacity) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    const auto e = boost::add_edge(from, to, G).first;
    const auto rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};

#define trace(x) //std::cout << #x << " = " << x << std::endl

void test_case() {
  int n, m, s, f; std::cin >> n >> m >> s >> f;
  // Create graph, edge adder class and propery maps
  graph G(n);
  auto c_map = boost::get(boost::edge_capacity, G);
  auto w_map = boost::get(boost::edge_weight, G);

  for (int i = 0; i < m; ++i) {
    int a, b, c, d; std::cin >> a >> b >> c >> d;
    edge e;
    e = boost::add_edge(a, b, G).first;
    c_map[e] = c;
    w_map[e] = d;
    e = boost::add_edge(b, a, G).first;
    c_map[e] = c;
    w_map[e] = d;
  }

  std::vector<int> dist_s(n);
  boost::dijkstra_shortest_paths(G, s,
    boost::distance_map(boost::make_iterator_property_map(
      dist_s.begin(), boost::get(boost::vertex_index, G))));
  std::vector<int> dist_f(n);
  boost::dijkstra_shortest_paths(G, f,
    boost::distance_map(boost::make_iterator_property_map(
      dist_f.begin(), boost::get(boost::vertex_index, G))));

  int distance = dist_s[f];
  
  graph G2(n);
  edge_adder adder(G2);
  edge_it ebeg, eend;
  for (boost::tie(ebeg, eend) = boost::edges(G); ebeg != eend; ++ebeg) {
    int source = boost::source(*ebeg, G), target = boost::target(*ebeg, G);
    if (dist_s[source] + w_map[*ebeg] + dist_f[target] == distance) {
      adder.add_edge(source, target, c_map[*ebeg]);
      trace(c_map[*ebeg]);
    }
  }

  long flow = boost::push_relabel_max_flow(G2, s, f);
  std::cout << flow << std::endl;
}


int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) test_case();
}
