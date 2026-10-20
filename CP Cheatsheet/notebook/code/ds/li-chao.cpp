struct LiChao {
  struct L {
    ll k, m;
    ll f(ll x) const { return k * x + m; }
  };
  int lo, hi;
  vector<L> t;
  LiChao(int a, int b)
      : lo(a), hi(b), t(4 * (b - a), {0, LLONG_MAX}) {}
  void add(L l, int v, int a, int b) {
    int m = a + (b - a) / 2;
    bool lef = l.f(a) < t[v].f(a), mid = l.f(m) < t[v].f(m);
    if (mid) swap(t[v], l);
    if (b - a == 1) return;
    if (lef != mid) add(l, 2 * v, a, m);
    else add(l, 2 * v + 1, m, b);
  }
  void seg(L l, int x, int y, int v, int a, int b) {
    if (y <= a || b <= x) return;
    if (x <= a && b <= y) return add(l, v, a, b);
    int m = a + (b - a) / 2;
    seg(l, x, y, 2 * v, a, m), seg(l, x, y, 2 * v + 1, m, b);
  }
  void add(ll k, ll m, int x, int y) {
    seg({k, m}, x, y, 1, lo, hi);
  }
  ll query(int x) {
    ll r = LLONG_MAX;
    for (int v = 1, a = lo, b = hi;; ) {
      r = min(r, t[v].f(x));
      if (b - a == 1) return r;
      int m = a + (b - a) / 2;
      if (x < m) v = 2 * v, b = m;
      else v = 2 * v + 1, a = m;
    }
  }
};
