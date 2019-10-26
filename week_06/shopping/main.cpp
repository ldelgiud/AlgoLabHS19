//STD includes
#include <iostream>
#include <vector>
// BGL include
#include <boost/graph/adjacency_list.hpp>
// BGL flow include *NEW*
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/edmonds_karp_max_flow.hpp>

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
boost::property<boost::edge_capacity_t, long,
boost::property<boost::edge_residual_capacity_t, long,
boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;
typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;

#define trace(x) //std::cout << #x << ": " << x << std::endl

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
  int n, m, s; std::cin >> n >> m >> s;

  graph G(n);
  const vertex_desc target = boost::add_vertex(G);
  auto c_map = boost::get(boost::edge_capacity, G);
  auto r_map = boost::get(boost::edge_reverse, G);
  edge_adder adder(G);

  for (int i = 0; i < s; ++i) {
    int tmp; std::cin >> tmp;
    edge_desc e; bool success;
    boost::tie(e, success) = boost::edge(tmp, target, G);
    if(success) {
      ++c_map[e];
    } else {
      adder.add_edge(tmp, target, 1);
    }
  }

  for (int i = 0; i < m; ++i) {
    int a, b; std::cin >> a >> b;
    adder.add_edge(a, b, 1);
    adder.add_edge(b, a, 1);
  }

  long flow = boost::push_relabel_max_flow(G, 0, target);

  if (flow == s) std::cout << "yes\n";
  else std::cout << "no\n";

}


int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) test_case();
}
