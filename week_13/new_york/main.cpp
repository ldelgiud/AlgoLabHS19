#include <iostream>
#include <vector>
#include <set>


#define step(x)  //std::cout << "STEP: " << x << std::endl
#define trace(x) //std::cout << #x <<  " = " << x << std::endl
void test_case() {
  int n, m, k; std::cin >> n >> m >> k;

  std::vector<long> temp;
  temp.reserve(n);
  for (int i = 0; i < n; ++i) {
    long t; std::cin >> t;
    temp.push_back(t);
  }

  std::vector<int> parent(n,0);
  std::vector<bool> leaf(n,true);
  for (int i = 0; i < n-1; ++i) {
    int u, v; std::cin >> u >> v;
    leaf[u] = false;
    parent[v] = u;
  }

  std::vector<bool> visited(n, false);
  std::vector<bool> start(n, false);
  for (int i = 0; i < n; ++i) {
    if (!leaf[i]) continue;
    trace(i);

    std::multiset<long> trip;
    trip.insert(temp[i]);
    int tail = i, curr = i;
    int l = 1;
    
    while (!visited[tail]) {

      long max = *(trip.rbegin());
      long min = *(trip.begin());

      if (max - min > k) {
	visited[tail] = true;
	trip.erase(trip.find(temp[tail]));
	tail = parent[tail];
	--l;
      } else if (l < m) {
	if (curr == parent[curr]) {
	  visited[tail] = true;
	  break;
	}
	curr = parent[curr];
	trip.insert(temp[curr]);
	++l;
      } else if (l == m) {
	visited[tail] = true;
	start[curr] = true;
	trip.erase(trip.find(temp[tail]));
	tail = parent[tail];
	--l;
      }
    }    
  }

  std::vector<int> sol;
  for (int i = 0; i < n; ++i) {
    if (start[i]) sol.push_back(i);
  }

  if (sol.size() == 0) {
    std::cout << "Abort mission\n";
  } else {
    for (int s : sol) {
      std::cout << s << ' ';
    }
    std::cout << std::endl;
  }
  
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) test_case();

}
