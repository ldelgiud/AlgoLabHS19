#include<iostream>
#include<vector>
#include<algorithm>
#include<deque>

using namespace std;


#define trace(x) cerr << #x << " = " << x << endl
#define step(x) cerr << "Step " << x << endl

void test_case() {
  int n; cin >> n;
  vector<int> word_count(n);
  int total_words = 0;

  for (int i = 0; i < n; ++i) {
    cin >> word_count[i];
    total_words += word_count[i];
  }
  //<position, word>
  vector<pair<int,int>> document;
  document.reserve(total_words);

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < word_count[i]; ++j) {
      int pos; cin >> pos;
      document.push_back(make_pair(pos, i));
    }
  }

  sort(document.begin(), document.end(), [](pair<int,int> a, pair<int,int> b)
  {
      return a.first < b.first;
  });

  /*for (int i = 0; i < document.size(); ++i) {
    cout << "(" << document[i].first << "," << document[i].second << ") ";
  }
  cout << endl;
  */
  vector<int> word_counter(n,0);
  int words_in_snippet = 1, best_size = 1<<30;
  deque<pair<int,int>> snippet;
  snippet.push_front(document[0]);
  int l = document[0].first, r = document[0].first;
  word_counter[document[0].second]++;

  for(int i = 1; i < document.size(); ++i) {

    //reduce window size
    while (words_in_snippet == n) {
      if((r-l+1) < best_size) {
          best_size = r-l+1;
      }
      auto tmp1 = snippet.back();
      snippet.pop_back();
      l += snippet.back().first - tmp1.first;
      if(!(--word_counter[tmp1.second])) {
        words_in_snippet--;
      }
    }


    auto tmp2 = snippet.front();
    auto word = document[i];
    snippet.push_front(word);
    r += word.first - tmp2.first;;
    word_counter[word.second]++;
    if(word_counter[word.second] == 1) words_in_snippet++;

    if(words_in_snippet == n && (r-l+1) < best_size) {
        best_size = r-l+1;
    }
  }


  cout << best_size << endl;
}


int main() {
  std::ios::sync_with_stdio(false);
  int t; cin >> t;
  while (t--) test_case();

}
