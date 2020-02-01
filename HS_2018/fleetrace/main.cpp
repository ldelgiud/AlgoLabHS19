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

typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator           out_edge_it; // Iterator

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

const int MAX = 50;
void test_case() {
  int B, S, P; std::cin >> B >> S >> P;
  const int N = B + S;
  graph G(N);
  auto c_map = boost::get(boost::edge_capacity, G);
  const int src = boost::add_vertex(G);
  const int src_ = boost::add_vertex(G);
  const int trg = boost::add_vertex(G);
  edge_adder adder(G);
  
  for (int i = 0; i < P; ++i) {
    int b, s, c; std::cin >> b >> s >> c;
    adder.add_edge(b, B+s, 1, MAX-c);
  }

  for (int i = 0; i < B; ++i) adder.add_edge(src_,   i, 1, 0);
  for (int i = 0; i < S; ++i) adder.add_edge(B+i, trg, 1, 0);
  adder.add_edge(src, src_, 500, 0);
  auto e = boost::edge(src, src_, G).first;
  int max_flow = boost::push_relabel_max_flow(G, src, trg);
  boost::successive_shortest_path_nonnegative_weights(G, src, trg);
  int cost = boost::find_flow_cost(G);
  int best_spectacle = max_flow*MAX - cost;

  for (int i = 0; i < max_flow; i++) {
    c_map[e] = i;
    int flow = boost::push_relabel_max_flow(G, src, trg);
    boost::successive_shortest_path_nonnegative_weights(G, src, trg);
    cost  = boost::find_flow_cost(G);
    int spectacle = flow*MAX -cost;
    if (best_spectacle < spectacle) {
      best_spectacle = spectacle;
    }
  }
  std::cout << best_spectacle << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) test_case();
}
