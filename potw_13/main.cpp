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

struct Request {
  int s, t, d, a, p, idx;
  Request(int s_, int t_, int d_, int a_, int p_) {
    s = s_; t = t_; d = d_; a = a_; p = p_;}
};

inline bool operator< (const Request& l, const Request& r) {return l.d < r.d;};
//inline bool operator< (const int l, const Request& r) {return l < r.d;};

#define trace(x)// std::cerr << #x << " = " << x << std::endl
#define step(x) //std::cerr << "STEP: " << x << std::endl
void test_case() {
  
  int N, S; std::cin >> N >> S;
  graph G;
  edge_adder adder(G);
  std::vector<int> cars; int max_cars = 0;
  for (int i = 0; i < S; ++i) {
    int l; std::cin >> l;
    cars.push_back(l);
    max_cars += l;
  }
  
  std::vector<std::set<int>> R(S);
  std::vector<Request> req;
  req.reserve(N);
  int max_time = 0;
  for (int i = 0; i < N; ++i) {
    int s, t, d, a, p; std::cin >> s >> t >> d >> a >> p;
    R[s-1].insert(d);
    R[t-1].insert(a);
    req.push_back(Request(s-1,t-1,d,a,p));
    max_time = std::max(max_time, a);
  }

  //maps time to vertex (=TTV)
  std::vector<std::map<int,int>> ttv(S);
  for (int i = 0; i < S; ++i) {
    R[i].insert(0);
    R[i].insert(max_time);
    for (auto it = R[i].begin(); it != R[i].end(); ++it) {
      ttv[i].insert({*it, boost::add_vertex(G)});
    }
  }
  const int src = boost::add_vertex(G);
  const int trg = boost::add_vertex(G);

  for (int i = 0; i < S; ++i) {
    auto it = R[i].begin();
    adder.add_edge(src, ttv[i][*it], cars[i], 0);
    for (; std::next(it) != R[i].end(); ++it) {
      adder.add_edge(ttv[i][*it], ttv[i][*std::next(it)], max_cars, 100*(*std::next(it)-*it));
    }
    adder.add_edge(ttv[i][*it], trg, max_cars, 0);
  }

  for (auto r : req) {
    int start = ttv[r.s][r.d];
    int end = ttv[r.t][r.a];
    adder.add_edge(start, end, 1, 100*(r.a-r.d)-r.p);
  }

  long offset = 100*max_time*max_cars;
  int flow1 = boost::push_relabel_max_flow(G, src, trg);
  boost::successive_shortest_path_nonnegative_weights(G, src, trg);
  int cost = boost::find_flow_cost(G);
  std::cout << offset - cost << "\n"; 
}



int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) test_case();
}
