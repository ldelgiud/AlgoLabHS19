// Algolab BGL Tutorial 2 (Max flow, by taubnert@ethz.ch)
// Flow example demonstrating how to use push_relabel_max_flow using a custom edge adder
// to manage the interior graph properties required for flow algorithms
#include <iostream>
#include <queue>
#include <vector>

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
typedef	boost::graph_traits<graph>::out_edge_iterator			out_edge_it;

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

  int g, s, l; std::cin >> g >> s >> l;
  graph G(g+s);
  auto rc_map = boost::get(boost::edge_residual_capacity, G);
  int src = boost::add_vertex(G);
  int trg = boost::add_vertex(G);
  edge_adder adder(G);  
  for (int i = 0; i < l; ++i) {
    int u, v; std::cin >> u >> v;
    adder.add_edge(u, g+v, 1);
  }
  for (int i = 0; i < g; ++i) {
    adder.add_edge(src, i, 1);
  }
  for (int i = 0; i < s; ++i) {
    adder.add_edge(g+i, trg, 1);
  }

  boost::push_relabel_max_flow(G, src, trg);

  // BFS to find vertex set S
  std::vector<int> vis(g+s+2, false); // visited flags
  std::queue<int> Q; // BFS queue (from std:: not boost::)
  vis[src] = true; // Mark the source as visited
  Q.push(src);
  while (!Q.empty()) {
    const int u = Q.front();
    Q.pop();
    out_edge_it ebeg, eend;
    for (boost::tie(ebeg, eend) = boost::out_edges(u, G); ebeg != eend; ++ebeg) {
      const int v = boost::target(*ebeg, G);
      // Only follow edges with spare capacity
      if (rc_map[*ebeg] == 0 || vis[v]) continue;
			vis[v] = true;
			Q.push(v);
    }
  }
  int cnt_1 = 0, cnt_2 = 0;
  for (int i = 0; i < g; ++i) {
    if (!vis[i]) ++cnt_1;
  }

  for (int i = 0; i < s; ++i) {
    if (vis[g+i]) ++cnt_2;
  }

  std::cout << cnt_1 << ' ' << cnt_2 << std::endl;
  for (int i  = 0; i < g+s; ++i) {
    if (i < g && !vis[i]) std::cout << i << ' ';
    if (i >= g && vis[i]) std::cout << i-g << ' '; 
  }
  std::cout << std::endl;
}



int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) test_case();

}
