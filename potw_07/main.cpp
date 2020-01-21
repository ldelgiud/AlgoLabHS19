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

const int INF = 1 << 25;
void test_case() {
  int Z, J;
  std::cin >> Z >> J;
  graph G(Z+J);
  const vertex_desc source = boost::add_vertex(G);
  const vertex_desc target = boost::add_vertex(G);
  edge_adder adder(G);
  
  for(int i = 0; i < Z; ++i) {
    int c; std::cin >> c;
    adder.add_edge(source, i, c);
  }

  long maximum = 0;
  for (int i = 0; i < J; ++i) {
    int r; std::cin >> r;
    maximum += r;
    adder.add_edge(Z+i, target, r);
  }

  for (int i = 0; i < J; ++i) {
    int N; std::cin >> N;
    for (int j = 0; j < N; ++j) {
      int z; std::cin >> z;
      adder.add_edge(z, Z+i, INF);
    }
  }

  long flow = boost::push_relabel_max_flow(G, source, target);

  std::cout << maximum - flow << std::endl;

}


int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) test_case();
}
