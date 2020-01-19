// Algolab BGL Tutorial 2 (Max flow, by taubnert@ethz.ch)
// Flow example demonstrating how to use push_relabel_max_flow using a custom edge adder
// to manage the interior graph properties required for flow algorithms
#include <iostream>

// BGL include
#include <boost/graph/adjacency_list.hpp>

// BGL flow include *NEW*
#include <boost/graph/push_relabel_max_flow.hpp>

// Graph Type with nested interior edge properties for flow algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;

typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;

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

void test_case() {
  int n, m, k, l; std::cin >> n >> m >> k >> l;
  graph G(2*n);
  edge_adder adder(G);
  int src = boost::add_vertex(G);
  int trg = boost::add_vertex(G);
  
  for (int i = 0; i < k; ++i) {
    int s; std::cin >> s;
    adder.add_edge(src, s, 1);
    adder.add_edge(n+s, trg, 1);
  }

  for (int i = 0; i < l; ++i) {
    int p; std::cin >> p;
    adder.add_edge(p, n+p, 1);
  }

  for (int i = 0; i < m; ++i) {
    int x, y; std::cin >> x >> y;
    adder.add_edge(x, y, k);
    adder.add_edge(n+x, n+y, 1);
  }

  long flow = boost::push_relabel_max_flow(G, src, trg);
  std:: cout << flow << std::endl;
  
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) test_case();
}
