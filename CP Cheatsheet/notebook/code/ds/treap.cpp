struct Treap {
  typedef ll T; // node value
  typedef ll L; // lazy tag
  T e = 0;      // merge identity
  L id = 0;     // tag that changes nothing
  T merge(T a, T b) { return a + b; }
  T apply(T x, L f, int len) { return x + f * len; }
  L comp(L f, L g) { return f + g; } // f applied after g
  struct Node { // rv: children still need reversing
    int l, r, sz; unsigned pri; T v, s; L lz; bool rv;
  };
  vector<Node> t{{0, 0, 0, 0, e, e, id, 0}}; // 0 = empty tree
  mt19937 rnd;
  int root = 0;
  int make(T v) {
    t.push_back({0, 0, 1, (unsigned)rnd(), v, v, id, 0});
    return sz(t) - 1;
  }
  void put(int x, L f) {
    if (!x) return;
    t[x].v = apply(t[x].v, f, 1), t[x].lz = comp(f, t[x].lz);
    t[x].s = apply(t[x].s, f, t[x].sz);
  }
  void push(int x) {
    Node& n = t[x];
    if (n.rv) swap(n.l, n.r), t[n.l].rv ^= 1, t[n.r].rv ^= 1;
    put(n.l, n.lz), put(n.r, n.lz), n.lz = id, n.rv = 0;
  }
  void pull(int x) {
    Node& n = t[x];
    n.sz = t[n.l].sz + 1 + t[n.r].sz;
    n.s = merge(merge(t[n.l].s, n.v), t[n.r].s);
  }
  pii split(int x, int k) { // first k elements go left
    if (!x) return {0, 0};
    push(x);
    int ls = t[t[x].l].sz;
    if (k <= ls) {
      auto [a, b] = split(t[x].l, k);
      t[x].l = b, pull(x);
      return {a, x};
    }
    auto [a, b] = split(t[x].r, k - ls - 1);
    t[x].r = a, pull(x);
    return {x, b};
  }
  int join(int a, int b) {
    if (!a || !b) return a ^ b;
    if (t[a].pri > t[b].pri) {
      push(a), t[a].r = join(t[a].r, b), pull(a);
      return a;
    }
    push(b), t[b].l = join(a, t[b].l), pull(b);
    return b;
  }

  void insert(int i, T v) { // v becomes position i
    auto [a, b] = split(root, i);
    root = join(join(a, make(v)), b);
  }
  void erase(int i) {
    auto [a, b] = split(root, i);
    root = join(a, split(b, 1).second);
  }
  // cut out [l, r), call f on its root, glue back
  template<class F> void on(int l, int r, F f) {
    auto [a, b] = split(root, l);
    auto [m, c] = split(b, r - l);
    f(m);
    root = join(join(a, m), c);
  }
  void update(int l, int r, L f) {
    on(l, r, [&](int m) { put(m, f); });
  }
  void reverse(int l, int r) { // needs merge commutative
    on(l, r, [&](int m) { t[m].rv ^= 1; });
  }
  T query(int l, int r) {
    T s = e; on(l, r, [&](int m) { s = t[m].s; }); return s;
  }
};
