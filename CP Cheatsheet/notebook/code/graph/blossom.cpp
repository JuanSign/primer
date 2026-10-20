struct Blossom {
  int n;
  vector<vi> g;
  vi mt, p, base, q;
  vector<bool> used, bl;
  Blossom(int N) : n(N), g(N), mt(N, -1), base(N) {}
  void addEdge(int a, int b) {
    g[a].push_back(b), g[b].push_back(a);
  }
  int lca(int a, int b) {
    vector<bool> u(n);
    for (;;) {
      a = base[a], u[a] = 1;
      if (mt[a] < 0) break;
      a = p[mt[a]];
    }
    for (;; b = p[mt[b]]) if (u[b = base[b]]) return b;
  }
  void mark(int v, int b, int ch) {
    for (; base[v] != b; v = p[mt[v]]) {
      bl[base[v]] = bl[base[mt[v]]] = 1;
      p[v] = ch, ch = mt[v];
    }
  }
  int find(int root) {
    used.assign(n, 0), p.assign(n, -1), iota(all(base), 0);
    used[root] = 1, q = {root};
    rep(qi, 0, sz(q)) for (int to : g[q[qi]]) {
      int v = q[qi];
      if (base[v] == base[to] || mt[v] == to) continue;
      if (to == root || (mt[to] >= 0 && p[mt[to]] >= 0)) {
        int b = lca(v, to);
        bl.assign(n, 0), mark(v, b, to), mark(to, b, v);
        rep(i, 0, n) if (bl[base[i]]) {
          base[i] = b;
          if (!used[i]) used[i] = 1, q.push_back(i);
        }
      } else if (p[to] < 0) {
        p[to] = v;
        if (mt[to] < 0) return to;
        used[mt[to]] = 1, q.push_back(mt[to]);
      }
    }
    return -1;
  }
  int run() {
    int res = 0;
    rep(v, 0, n) if (mt[v] < 0)
      for (int u = find(v); u >= 0;) {
        int pv = p[u], nu = mt[pv];
        mt[u] = pv, mt[pv] = u, u = nu, res += u < 0;
      }
    return res;
  }
};
