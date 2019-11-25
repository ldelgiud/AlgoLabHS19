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
  edge_desc add_edge(int from, int to, long capacity, long cost) {
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
    return e;
  }
};


void test_case() {
  int n, g, budget, src, tar;
  std::cin >> n >> g >> budget >> src >> tar;
  
  graph G(n);
  const int start = boost::add_vertex(G);
 
  edge_adder adder(G);  
  auto c_map = boost::get(boost::edge_capacity, G);
  auto r_map = boost::get(boost::edge_reverse, G);
  // auto rc_map = boost::get(boost::edge_residual_capacity, G);
  auto w_map = boost::get(boost::edge_weight, G); // new!

  for (int i = 0; i < g; ++i) {
    int x, y, d, e; std::cin >> x >> y >> d >> e;
    adder.add_edge(x, y, e, d);
  }

   long max_flow = boost::push_relabel_max_flow(G, src, tar);
   boost::successive_shortest_path_nonnegative_weights(G, src, tar);
   long max_cost = boost::find_flow_cost(G);
   //Early stop
   if (budget >= max_cost) {
     std::cout << max_flow << std::endl;
     return;
   }

   //Binary search in [0,max_flow]
   edge_desc e1 = adder.add_edge(start, src, 0, 0);
   long min_flow = 0;
   long flow = max_flow;
   long cost = max_cost;
   while (max_flow > min_flow) {
     long mid =  (max_flow+min_flow)/2;
     c_map[e1] = mid;

     flow = boost::push_relabel_max_flow(G, start, tar);
     boost::successive_shortest_path_nonnegative_weights(G, start, tar);
     cost = boost::find_flow_cost(G);

     if (cost > budget) {
       max_flow = mid;
     } else if (cost <= budget) {
       min_flow = mid+1;
     } //else break;
   }

   //linear search at the end
   long prev_flow = flow;
   do {
     prev_flow = flow;
     --c_map[e1];
     flow = boost::push_relabel_max_flow(G, start, tar);
     boost::successive_shortest_path_nonnegative_weights(G, start, tar);
     cost = boost::find_flow_cost(G);
     
   } while (cost > budget);

   do {
     prev_flow = flow;
     ++c_map[e1];
     flow = boost::push_relabel_max_flow(G, start, tar);
     boost::successive_shortest_path_nonnegative_weights(G, start, tar);
     cost = boost::find_flow_cost(G);
     
   } while (cost <= budget);
   
  
   std::cout << prev_flow << std::endl;

}


int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) test_case();

}
