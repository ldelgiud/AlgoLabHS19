#include<iostream>
#include<vector>

using namespace std;

#define trace(x)// cerr << #x << " = " << x << endl
#define step(x) //cerr << "Step " << x << endl

vector<vector<int>> G;
int n, m;
vector<int> min_steps;
vector<int> max_steps;

static bool MY_BALL = true;
static bool HIS_BALL =  false;
static int MORIARTY = 1;
static int HOLMES = 0;

int play(int pos, bool turn);

void test_case() {
  cin >> n >> m;
  trace(n);
  int r, b; cin >> r >> b;

  G.clear();
  G = vector<vector<int>>(n+1);
  for (int i = 0; i < m; ++i) {
      int u, v; cin >> u >> v;
      G[u].push_back(v);
  }

  min_steps.clear();
  max_steps.clear();
  min_steps = vector<int>(n+1,-1);
  max_steps = vector<int>(n+1,-1);

  int red = play(r, MY_BALL);
  int black = play(b, MY_BALL);

  if (red < black) cout << HOLMES << endl;
  else if (red > black) cout << MORIARTY << endl;
  else {
    if ((red%2)== 0) cout << MORIARTY << endl;
    else  cout << HOLMES << endl;
  }
}

int play(int pos, bool turn) {
  if (pos == n) return 0;

  if(turn == MY_BALL) {
    int max_dist = 1 << 30;
    trace(pos);
    if (min_steps[pos] == -1) {
      for (int v : G[pos]) {
        max_dist = min(max_dist, play(v,HIS_BALL));
      }
      min_steps[pos] = 1 + max_dist;
    }
    return min_steps[pos];
  } else {
    int min_dist = 0;
    if (max_steps[pos] == -1){
      for (int v : G[pos]) {
        min_dist = max(min_dist, play(v,MY_BALL));
      }
      max_steps[pos] = 1 + min_dist;
    }
    return max_steps[pos];
  }
}
int main() {
  std::ios::sync_with_stdio(false);
  int t; cin >> t;
  while (t--) test_case();

}
