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

#define trace(x) //std::cout << #x << " = " << x << std::endl;

void test_case() {
  int l, q; std::cin >> l >> q;
  graph G(l);
  edge_adder adder(G);
  const int src = boost::add_vertex(G);
  const int trg = boost::add_vertex(G);

  int total = 0;
  std::vector<int> demand;
  demand.reserve(l);
  for (int i = 0; i < l; ++i) {
    int g, d; std::cin >> g >> d;
    int diff = d-g;
    demand.push_back(diff);
    trace(diff);
  }

  for (int i = 0; i < q; ++i) {
    int u, v, c, C; std::cin >> u >> v >> c >> C;
    demand[u] += c;
    demand[v] -= c;
    adder.add_edge(u, v, C-c);
  }

  for (int i = 0; i < l; ++i) {
    trace(demand[i]);
    if (demand[i] < 0) {
      adder.add_edge(src, i, -demand[i]);
    } else if (demand[i] > 0) {
      adder.add_edge(i, trg, demand[i]);
      total += demand[i];
    }
  }

  long flow = boost::push_relabel_max_flow(G, src, trg);
  trace(flow);
  trace(total);
  if (flow == total) std::cout << "yes\n";
  else std::cout << "no\n";
}



int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) test_case();
}
