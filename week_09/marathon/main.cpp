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
#include <boost/graph/dijkstra_shortest_paths.hpp>

// Graph Type with nested interior edge properties for Cost Flow Algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > graph; // new! weightmap corresponds to costs

typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator           out_edge_it; // Iterator
typedef boost::property_map<graph, boost::edge_weight_t>::type weight_map;
// Custom edge adder class
class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}
  void add_edge(int from, int to, long capacity, long cost) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto w_map = boost::get(boost::edge_weight, G); // new!
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
    w_map[e] = cost;   // new assign cost
    w_map[rev_e] = -cost;   // new negative cost
  }
};

#define step(x)// std::cout << "STEP: " << x << std::endl;
#define trace(x) //std::cout << #x << " = " << x << std::endl;

void test_case() {
  int n, m, s, f; std::cin >> n >> m >> s>> f;
  trace(s);
  trace(f);
  step("READ");
  graph G(n);
  weight_map weights = boost::get(boost::edge_weight, G);
  auto c_map = boost::get(boost::edge_capacity, G);
  
  for (int i = 0; i < m; ++i) {
    int a, b, c, d; std::cin >> a >> b >> c >> d;
    edge_desc e = boost::add_edge(a, b, G).first;
    weights[e] = d;
    c_map[e] = c;
     e = boost::add_edge(b, a, G).first;
    weights[e] = d;
    c_map[e] = c;
  }

  step("Shortest path");
  std::vector<int> dist_s(n);
  std::vector<int> pred_s(n);
  boost::dijkstra_shortest_paths(G, s,
    boost::distance_map(boost::make_iterator_property_map(
      dist_s.begin(), boost::get(boost::vertex_index, G)))
    .predecessor_map(boost::make_iterator_property_map(
      pred_s.begin(), boost::get(boost::vertex_index, G))));
  std::vector<int> dist_f(n);
  std::vector<int> pred_f(n);
  boost::dijkstra_shortest_paths(G, f,
    boost::distance_map(boost::make_iterator_property_map(
      dist_f.begin(), boost::get(boost::vertex_index, G)))
    .predecessor_map(boost::make_iterator_property_map(
      pred_f.begin(), boost::get(boost::vertex_index, G))));


  step("read edges");
  int distance  = dist_s[f];
  trace(distance);
  graph G2(n);
  edge_adder adder(G2);
  for (auto it = boost::edges(G).first; it != boost::edges(G).second; ++it) {
    int tot_dist = dist_s[boost::source(*it, G)] + weights[*it] + dist_f[boost::target(*it, G)];
    trace(boost::source(*it, G));
    trace(boost::target(*it, G));

    if (tot_dist <= distance) {
      
      adder.add_edge(boost::source(*it, G),
		     boost::target(*it, G),
		     c_map[*it],
		     0);  
    }
  }

  step("flow");
  int flow = boost::push_relabel_max_flow(G2, s, f);
  std::cout << flow << std::endl;
}


int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t; 
  while (t--) test_case();

}
