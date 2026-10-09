struct RollbackDSU {
  vi p;          // p[x] < 0: x is a root, set size -p[x]
  vector<pii> h; // undo stack: {attached root, its old p}
  RollbackDSU(int n) : p(n, -1) {}
  int find(int x) { return p[x] < 0 ? x : find(p[x]); }
  int size(int x) { return -p[find(x)]; }
  int time() { return sz(h); }
  bool join(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    if (p[a] > p[b]) swap(a, b); // a is the bigger set
    h.push_back({b, p[b]});
    p[a] += p[b], p[b] = a;
    return true;
  }
  void rollback(int t) { // undo joins until time() == t
    while (time() > t) {
      auto [b, pb] = h.back();
      h.pop_back();
      p[p[b]] -= pb, p[b] = pb;
    }
  }
};
