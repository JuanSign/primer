// counts: cnt[v]++ at each text step, then for v in
// reverse q: cnt[link[v]] += cnt[v]
struct AhoCorasick {
  enum { A = 26, F = 'a' };
  vector<array<int, A>> nx{{}};
  vi link{0}, out{0}, q;
  int add(const string& s) {
    int v = 0;
    for (char ch : s) {
      int c = ch - F;
      if (!nx[v][c]) nx[v][c] = sz(nx), nx.push_back({}),
        link.push_back(0), out.push_back(0);
      v = nx[v][c];
    }
    out[v]++;
    return v;
  }
  void build() {
    q = {0};
    rep(i, 0, sz(q)) {
      int v = q[i];
      if (v) out[v] += out[link[v]];
      rep(c, 0, A) {
        int& u = nx[v][c];
        if (!u) u = nx[link[v]][c];
        else link[u] = v ? nx[link[v]][c] : 0, q.push_back(u);
      }
    }
  }
};
