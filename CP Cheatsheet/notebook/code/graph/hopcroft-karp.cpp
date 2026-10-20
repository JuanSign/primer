struct HopcroftKarp {
  vector<vi> g;
  vi l, r, d;
  HopcroftKarp(int n, int m) : g(n), l(n, -1), r(m, -1) {}
  void addEdge(int a, int b) { g[a].push_back(b); }
  bool bfs() {
    d.assign(sz(g), -1);
    vi q;
    rep(a, 0, sz(g)) if (l[a] < 0) d[a] = 0, q.push_back(a);
    bool ok = 0;
    rep(i, 0, sz(q)) for (int b : g[q[i]]) {
      int c = r[b];
      if (c < 0) ok = 1;
      else if (d[c] < 0) d[c] = d[q[i]] + 1, q.push_back(c);
    }
    return ok;
  }
  bool dfs(int a) {
    for (int b : g[a]) {
      int c = r[b];
      if (c < 0 || (d[c] == d[a] + 1 && dfs(c))) {
        l[a] = b, r[b] = a;
        return 1;
      }
    }
    d[a] = -1;
    return 0;
  }
  int run() {
    int res = 0;
    while (bfs()) rep(a, 0, sz(g)) if (l[a] < 0) res += dfs(a);
    return res;
  }
};
