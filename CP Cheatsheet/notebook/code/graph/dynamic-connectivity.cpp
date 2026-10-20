struct DynCon {
  int q;
  vector<vector<pii>> t;
  map<pii, int> open;
  DynCon(int Q) : q(Q), t(4 * Q) {}
  void ins(int l, int r, pii e, int v, int lo, int hi) {
    if (r <= lo || hi <= l) return;
    if (l <= lo && hi <= r) return t[v].push_back(e);
    int m = (lo + hi) / 2;
    ins(l, r, e, 2 * v, lo, m), ins(l, r, e, 2 * v + 1, m, hi);
  }
  void toggle(int i, int a, int b) {
    pii e = minmax(a, b);
    auto it = open.find(e);
    if (it == open.end()) open[e] = i;
    else ins(it->second, i, e, 1, 0, q), open.erase(it);
  }
  template<class F>
  void run(RollbackDSU& d, F f, int v, int lo, int hi) {
    int t0 = d.time();
    for (auto [a, b] : t[v]) d.join(a, b);
    if (hi - lo == 1) f(lo);
    else {
      int m = (lo + hi) / 2;
      run(d, f, 2 * v, lo, m), run(d, f, 2 * v + 1, m, hi);
    }
    d.rollback(t0);
  }
  template<class F> void run(RollbackDSU& d, F f) {
    for (auto [e, i] : open) ins(i, q, e, 1, 0, q);
    run(d, f, 1, 0, q);
  }
};
