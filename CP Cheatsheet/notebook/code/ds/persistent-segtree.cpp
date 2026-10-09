struct PersistentSegTree {
  struct Node { int l, r; ll s; };
  vector<Node> t{{0, 0, 0}}; // root 0 = all zeros
  int n;
  PersistentSegTree(int N) : n(N) {}
  // new root: version v with a[i] += x
  int add(int v, int i, ll x) { return add(v, i, x, 0, n); }
  int add(int v, int i, ll x, int lo, int hi) {
    int u = sz(t);
    t.push_back(t[v]);
    t[u].s += x;
    if (hi - lo == 1) return u;
    int m = (lo + hi) / 2;
    if (i < m) t[u].l = add(t[v].l, i, x, lo, m);
    else t[u].r = add(t[v].r, i, x, m, hi);
    return u;
  }
  // sum of [l, r) in version v
  ll query(int v, int l, int r) {
    return query(v, l, r, 0, n);
  }
  ll query(int v, int l, int r, int lo, int hi) {
    if (!v || r <= lo || hi <= l) return 0;
    if (l <= lo && hi <= r) return t[v].s;
    int m = (lo + hi) / 2;
    return query(t[v].l, l, r, lo, m) +
           query(t[v].r, l, r, m, hi);
  }
  // k-th (0-indexed) unit of version b minus version a
  int kth(int a, int b, ll k) {
    int lo = 0, hi = n;
    while (hi - lo > 1) {
      int m = (lo + hi) / 2;
      ll c = t[t[b].l].s - t[t[a].l].s;
      if (k < c) a = t[a].l, b = t[b].l, hi = m;
      else k -= c, a = t[a].r, b = t[b].r, lo = m;
    }
    return lo;
  }
};
