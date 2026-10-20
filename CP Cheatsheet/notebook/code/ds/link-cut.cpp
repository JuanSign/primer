struct LinkCut {
  struct N {
    int c[2] = {}, p = 0;
    bool rv = 0;
    ll v = 0, s = 0;
  };
  vector<N> t;
  LinkCut(int n) : t(n + 1) {}
  bool root(int x) {
    int p = t[x].p;
    return t[p].c[0] != x && t[p].c[1] != x;
  }
  void pull(int x) {
    t[x].s = t[t[x].c[0]].s + t[x].v + t[t[x].c[1]].s;
  }
  void push(int x) {
    if (!t[x].rv) return;
    swap(t[x].c[0], t[x].c[1]), t[x].rv = 0;
    for (int y : t[x].c) if (y) t[y].rv ^= 1;
  }
  void rot(int x) {
    int p = t[x].p, g = t[p].p, d = t[p].c[1] == x;
    if (!root(p)) t[g].c[t[g].c[1] == p] = x;
    t[x].p = g, t[p].c[d] = t[x].c[!d];
    if (t[x].c[!d]) t[t[x].c[!d]].p = p;
    t[x].c[!d] = p, t[p].p = x;
    pull(p), pull(x);
  }
  void splay(int x) {
    vi st{x};
    for (int y = x; !root(y); y = t[y].p) st.push_back(t[y].p);
    for (int i = sz(st); i--;) push(st[i]);
    while (!root(x)) {
      int p = t[x].p, g = t[p].p;
      if (!root(p))
        rot((t[g].c[1] == p) == (t[p].c[1] == x) ? p : x);
      rot(x);
    }
  }
  void access(int x) {
    for (int y = 0; x; y = x, x = t[x].p)
      splay(x), t[x].c[1] = y, pull(x);
  }
  void makeRoot(int x) { access(x), splay(x), t[x].rv ^= 1; }
  int findRoot(int x) {
    access(x), splay(x);
    while (push(x), t[x].c[0]) x = t[x].c[0];
    splay(x);
    return x;
  }
  void link(int a, int b) { makeRoot(a), t[a].p = b; }
  void cut(int a, int b) {
    makeRoot(a), access(b), splay(b);
    t[b].c[0] = t[a].p = 0, pull(b);
  }
  ll query(int a, int b) {
    makeRoot(a), access(b), splay(b);
    return t[b].s;
  }
  void set(int x, ll v) {
    access(x), splay(x), t[x].v = v, pull(x);
  }
};
