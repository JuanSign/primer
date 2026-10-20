struct Dinic {
  struct E { int to, rev; ll c, oc; };
  vector<vector<E>> g;
  vi lvl, ptr, q;
  Dinic(int n) : g(n), lvl(n), ptr(n), q(n) {}
  void addEdge(int a, int b, ll c, ll rc = 0) {
    g[a].push_back({b, sz(g[b]), c, c});
    g[b].push_back({a, sz(g[a]) - 1, rc, rc});
  }
  ll dfs(int v, int t, ll f) {
    if (v == t || !f) return f;
    for (int& i = ptr[v]; i < sz(g[v]); i++) {
      E& e = g[v][i];
      if (lvl[e.to] == lvl[v] + 1)
        if (ll p = dfs(e.to, t, min(f, e.c))) {
          e.c -= p, g[e.to][e.rev].c += p;
          return p;
        }
    }
    return 0;
  }
  ll calc(int s, int t) {
    ll flow = 0;
    q[0] = s;
    rep(L, 0, 31) do {
      lvl = ptr = vi(sz(q));
      int qi = 0, qe = lvl[s] = 1;
      while (qi < qe && !lvl[t]) {
        int v = q[qi++];
        for (E e : g[v])
          if (!lvl[e.to] && e.c >> (30 - L))
            q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
      }
      while (ll p = dfs(s, t, LLONG_MAX)) flow += p;
    } while (lvl[t]);
    return flow;
  }
  bool leftOfMinCut(int a) { return lvl[a] != 0; }
};
