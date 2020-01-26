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

struct Request {
  int s, t, d, a, p, idx;
  Request(int s_, int t_, int d_, int a_, int p_, int idx_) {
    s = s_; t = t_; d = d_; a = a_; p = p_; idx = idx_;}
};

inline bool operator< (const Request& l, const Request& r) {return l.d < r.d;};
//inline bool operator< (const int l, const Request& r) {return l < r.d;};

#define trace(x) //std::cout << #x << " = " << x << std::endl

void test_case() {
  int N, S; std::cin >> N >> S;

  graph G(N+S);
  const int src = boost::add_vertex(G);
  const int trg = boost::add_vertex(G);
  edge_adder adder(G);
  
  for (int i = 0; i < S; ++i) {
    int l; std::cin >> l;
    adder.add_edge(src, i, l, 0);
    adder.add_edge(i, trg, l, 0);
  }

  std::vector<std::multiset<Request>> R(S);
  for (int i = 0; i < N; ++i) {
    int s, t, d, a, p; std::cin >> s >> t >> d >> a >> p;
    R[s-1].insert(Request(s-1,t-1,d,a,p,i));
 
  }
  int cnt = 0;
  for (int i = 0; i < S; ++i) {
    for (auto it = R[i].begin(); it != R[i].end(); ++it) {
      adder.add_edge(it->s, S+it->idx, 1, -it->p);
      adder.add_edge(S+it->idx, trg, 1, 0);
      
      Request tmp(1,1, it->a, it->a, 1, 1);
      
      for (auto it2 = R[it->t].lower_bound(tmp); it2 != R[it->t].end(); ++it2) {
	adder.add_edge(S+it->idx, S+it2->idx, 1, -it2->p);
	trace(cnt++);
      }
    }
  }
  trace(cnt);
  // Option 1: Min Cost Max Flow with cycle_canceling
  int flow1 = boost::push_relabel_max_flow(G, src, trg);
  boost::cycle_canceling(G);
  int cost1 = boost::find_flow_cost(G);
  std::cout << -cost1 << "\n"; 
  trace(cnt);
}



int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) test_case();
}
