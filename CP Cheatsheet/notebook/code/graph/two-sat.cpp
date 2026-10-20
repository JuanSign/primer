struct TwoSat {
  vector<vi> g;
  vector<bool> val;
  TwoSat(int n) : g(2 * n), val(n) {}
  void either(int a, int b) {
    g[a ^ 1].push_back(b), g[b ^ 1].push_back(a);
  }
  void imply(int a, int b) { either(a ^ 1, b); }
  bool solve() {
    SCC s(g);
    rep(x, 0, sz(val)) {
      if (s.comp[2 * x] == s.comp[2 * x + 1]) return false;
      val[x] = s.comp[2 * x] < s.comp[2 * x + 1];
    }
    return true;
  }
};
