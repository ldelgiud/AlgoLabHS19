#include <iostream> 
#include <vector>
#include <utility>
#include <string>
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

#define trace(x)// std::cout << #x << ": " << x << std::endl
#define trace_vec(x) for (auto val: x) {std::cout << val << ' ';} std::cout << std::endl

void test_case() {
  int h, w; std::cin >> h >> w;
  const int A = (int) 'A';
  const int Z = (int) 'Z';
  const int symbols = Z-A+1;
  graph G(symbols + symbols*symbols);
  vertex_desc source = boost::add_vertex(G);
  vertex_desc target = boost::add_vertex(G);
  edge_adder adder(G);
  auto c_map = boost::get(boost::edge_capacity, G);
  auto r_map = boost::get(boost::edge_reverse, G);

  //read line
  std::string str;
  std::cin >> str;

  std::vector<std::vector<int>> page(h);
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      char tmp; std::cin >> tmp;
      page[i].push_back(symbols*((int)tmp-A));
    }
  }

  std::vector<int> L(symbols*symbols,0);
  
  for (int i = 0; i < h; ++i) {
    for (int j = w-1; j>=0 ; --j) {
      char tmp; std::cin >> tmp;
      tmp -= A;
      int node = page[i][j] + tmp;
      ++L[node];
    }
  }

  int cnt = 0;
  for (char c: str) {
    int tmp = (int) c - A;
    edge_desc e; bool success;
    boost::tie(e,success) = boost::edge(source,tmp,G);
    if(success) ++c_map[e];
    else adder.add_edge(source, tmp, 1);
    cnt++;
  }

  
  for (int i = 0; i < L.size(); ++i) {
    if (L[i]) {
      int l2 = i%symbols;
      int l1 = i/symbols;
      adder.add_edge(l1, symbols+i, L[i]);
      adder.add_edge(l2, symbols+i, L[i]);
      adder.add_edge(symbols+i, target,L[i]);
    }
  }

  long flow = boost::push_relabel_max_flow(G, source, target);
  
  //long flow = boost::edmonds_karp_max_flow(G, source, target);
  trace(flow);
  trace(cnt);
  if (flow >= cnt) std::cout << "Yes\n";
  else std::cout << "No\n";


  
  
}


int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) test_case();
}
