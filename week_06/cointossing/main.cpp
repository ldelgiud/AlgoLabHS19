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
  int n,m; std::cin >> n >> m;
  trace(n);
  trace(m);

  graph G(n);
  const vertex_desc s = boost::add_vertex(G);
  const vertex_desc t = boost::add_vertex(G);
  edge_adder adder(G);
  long games = 0;
  std::vector<long> points(n,0);
  for (int i = 0; i < m; ++i) {
    int a, b, c;
    std::cin >> a >> b >> c;

    if (c == 0) {
      vertex_desc game = boost::add_vertex(G);
      adder.add_edge(s, game, 1);
      adder.add_edge(game, a, 1);
      adder.add_edge(game, b, 1);
      ++games;
    } else if (c == 1) {
      ++points[a];
    } else if (c == 2) {
      ++points[b];
    }
  }

  long sum = 0;
  bool flag = false;
  for (int i = 0; i < n; ++i) {
    long s_i; std::cin >> s_i;
    long tmp = s_i - points[i];
    if (tmp < 0) {
      flag = true;
    }
    sum += tmp;
    adder.add_edge(i, t, tmp);
  }
  if (flag) {
    std::cout << "no\n";
    return;
  }

  long flow = boost::push_relabel_max_flow(G, s, t);

  if (flow == sum && flow == games ) {
    std::cout << "yes\n";
  } else std::cout << "no\n";
}


int main(){
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) test_case();
}
