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
  int w, n; std::cin >> w >> n;

  graph G(2*(w+1));
  const int source = 0;
  const int target = 2*w + 1;
  edge_adder adder(G);

  for (int i = 1; i < w; ++i) {
    adder.add_edge(2*i,2*i+1,1);
  }
  adder.add_edge(source,1,1<<20);
  adder.add_edge(2*w, target, 1<<20);

  for (int i = 0; i < n; ++i) {
    int a,b; std::cin >> a >> b;
    if (a < b) {
      adder.add_edge(2*a+1,2*b,1);
    } else {
      adder.add_edge(2*b+1,2*a,1);
    }
  }

  long flow = boost::push_relabel_max_flow(G, source, target);

  std::cout << flow << std::endl;
}


int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) test_case();
}
