// occurrences: for v from last node down to 2,
// cnt[link[v]] += cnt[v]
struct Eertree {
  vector<array<int, 26>> nx{{}, {}};
  vi len{-1, 0}, link{0, 0}, cnt{0, 0};
  string s;
  int last = 1;
  int get(int v, int i) {
    while (i - len[v] < 1 || s[i - len[v] - 1] != s[i])
      v = link[v];
    return v;
  }
  void add(char ch) {
    s += ch;
    int i = sz(s) - 1, c = ch - 'a', v = get(last, i);
    if (!nx[v][c]) {
      int w = len[v] == -1 ? 1 : nx[get(link[v], i)][c];
      nx.push_back({}), len.push_back(len[v] + 2);
      link.push_back(w), cnt.push_back(0);
      nx[v][c] = sz(len) - 1;
    }
    cnt[last = nx[v][c]]++;
  }
};
