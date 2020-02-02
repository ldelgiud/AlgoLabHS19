// ALGOLAB BGL Tutorial 3
// Code demonstrating 
// - MinCostMaxFlow with arbitrary edge costs using cycle_canceling
// - MinCostMaxFlow with non-negative edge costs using successive_shortest_path_nonnegative_weights

// Includes
// ========
#include <iostream>
#include <map>
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

#define trace(x) std::cout << #x << " = " << x << std::endl;

struct Trip {
  int start, end, price;

  Trip(int s, int e, int p) {start = s; end = e; price = p;}
};

inline bool operator<(const Trip &l, const Trip &r) {
  if (l.start == r.start) {
    if (l.end == r.end) {
      return l.price < r.price;
    } else return l.end < r.end;
  } else return l.start < r.start;
}
const int MAX = 128;
void test_case() {
  int n, m; std::cin >> n >> m;
  graph G(n);
  edge_adder adder(G);
  const int src = boost::add_vertex(G);
  const int trg = n-1;

  int prev = 0, total = 0; 

  for (int i = 0; i < n-1; ++i) {
    int c; std::cin >> c;
    adder.add_edge(i, i+1, c, MAX);
    if (prev > c) adder.add_edge(i, trg, prev-c, 0);
    else if (prev < c) adder.add_edge(src, i, c-prev, 0);
    total += c;
    prev = c;
  }
  // <trip = key, int = counter> 
  std::map<Trip, int> M;
  for (int i = 0; i < m; ++i) {
    int a, b, d; std::cin >> a >> b >> d;
    auto it = M.find(Trip(a,b,d));
    if (it == M.end()) M.insert({Trip(a,b,d),1});
    else (it->second)++;
  }

  for (auto it = M.begin(); it != M.end(); ++it) {
    Trip t = it->first;
    int cap = it->second;
    adder.add_edge(t.start, t.end, cap, MAX*(t.end-t.start)-t.price);
  }

  int flow = boost::push_relabel_max_flow(G, src, trg);
  boost::successive_shortest_path_nonnegative_weights(G, src, trg);
  int cost = boost::find_flow_cost(G);
  std::cout << total*MAX - cost << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) test_case();
}
