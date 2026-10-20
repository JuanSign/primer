struct LCA {
  int k, t = 0;
  vector<vi> up;
  vi d, tin, tout;
  LCA(const vector<vi>& g, int r = 0)
      : k(__lg(sz(g)) + 1), up(k, vi(sz(g))), d(sz(g)),
        tin(sz(g)), tout(sz(g)) { dfs(g, r, r); }
  void dfs(const vector<vi>& g, int v, int p) {
    tin[v] = t++, up[0][v] = p;
    rep(j, 1, k) up[j][v] = up[j - 1][up[j - 1][v]];
    for (int u : g[v])
      if (u != p) d[u] = d[v] + 1, dfs(g, u, v);
    tout[v] = t;
  }
  bool anc(int a, int b) {
    return tin[a] <= tin[b] && tout[b] <= tout[a];
  }
  int lca(int a, int b) {
    if (anc(a, b)) return a;
    for (int j = k; j--;) if (!anc(up[j][a], b)) a = up[j][a];
    return up[0][a];
  }
  int jump(int v, int s) {
    rep(j, 0, k) if (s >> j & 1) v = up[j][v];
    return v;
  }
  int dist(int a, int b) {
    return d[a] + d[b] - 2 * d[lca(a, b)];
  }
};
