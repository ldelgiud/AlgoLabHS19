#include <iostream>
#include <string>
#include <map>
#include <set>
#include <utility>

#include <boost/graph/adjacency_list.hpp>
#include <cassert>
#include <boost/graph/max_cardinality_matching.hpp>


typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property,                         // no vertex property
  boost::property<boost::edge_weight_t, int>  // interior edge weight property
> Graph;
typedef boost::property_map<Graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<Graph>::edge_descriptor            Edge;
typedef boost::graph_traits<Graph>::vertex_descriptor          Vertex;
typedef boost::graph_traits<Graph>::edge_iterator              edge_it;

#define trace(x) // std::cout << #x << " = " << x << std::endl
void test_case() {
  int n, c, f;
  std::cin >> n >> c >> f;
  //<characteristic, person>
  std::multimap<std::string, int> M;
  std::set<std::string> args;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < c; ++j) {
      std::string str;
      std::cin >> str;
      M.insert(make_pair(str,i));
      args.insert(str);
    }
  }

  Graph G(n);
  weight_map weights = boost::get(boost::edge_weight, G);

  for (std::string str: args) {
    auto range = M.equal_range(str);
    for (auto i = range.first; i != range.second; ++i) {
        for (auto j = i; j != range.second; ++j) {
          if (j == i) continue;
          Edge e; bool success;
          boost::tie(e, success) = boost::edge(i->second,j->second,G);
          if (success) ++weights[e];
          else {
            boost::tie(e, success) = boost::add_edge(i->second,j->second,G);
            weights[e] = 1;
          }
        }
    }
  }

  trace(n);
  std::vector<std::pair<int,int>> vec;

  edge_it ebeg, eend;
  for (boost::tie(ebeg, eend) = boost::edges(G); ebeg != eend; ++ebeg) {
    int u = boost::source(*ebeg, G), v = boost::target(*ebeg, G);
    trace(u);
    trace(v);
    trace(weights[*ebeg]);
    if (weights[*ebeg] <= f) vec.push_back(std::make_pair(u,v));
  }

  Graph G2(n);
  for (auto p: vec) {
    boost::add_edge(p.first, p.second, G2);
  }

  std::vector<Vertex> matemap(n);

   boost::edmonds_maximum_cardinality_matching(G2,
       boost::make_iterator_property_map(matemap.begin(),
       boost::get(boost::vertex_index,G2)));

   int matchsize = boost::matching_size(G2,
       boost::make_iterator_property_map(matemap.begin(),
       boost::get(boost::vertex_index,G2)));

   if(matchsize == n/2)
     std::cout << "not optimal" << std::endl;
   else
     std::cout << "optimal" << std::endl;
}

int main() {

  int t; std::cin >> t;
  while(t--) test_case();


}
