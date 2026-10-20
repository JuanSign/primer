struct HLD {
  vi par, dep, heavy, head, pos, sub;
  int t = 0;
  HLD(const vector<vi>& g, int r = 0)
      : par(sz(g), -1), dep(sz(g)), heavy(sz(g), -1),
        head(sz(g)), pos(sz(g)), sub(sz(g), 1) {
    dfs(g, r), build(g, r, r);
  }
  void dfs(const vector<vi>& g, int v) {
    for (int u : g[v]) if (u != par[v]) {
      par[u] = v, dep[u] = dep[v] + 1, dfs(g, u);
      sub[v] += sub[u];
      if (heavy[v] < 0 || sub[u] > sub[heavy[v]]) heavy[v] = u;
    }
  }
  void build(const vector<vi>& g, int v, int h) {
    head[v] = h, pos[v] = t++;
    if (heavy[v] >= 0) build(g, heavy[v], h);
    for (int u : g[v])
      if (u != par[v] && u != heavy[v]) build(g, u, u);
  }
  template<class F> void path(int a, int b, F f, bool e = 0) {
    for (; head[a] != head[b]; b = par[head[b]]) {
      if (dep[head[a]] > dep[head[b]]) swap(a, b);
      f(pos[head[b]], pos[b] + 1);
    }
    if (dep[a] > dep[b]) swap(a, b);
    f(pos[a] + e, pos[b] + 1);
  }
  int lca(int a, int b) {
    for (; head[a] != head[b]; b = par[head[b]])
      if (dep[head[a]] > dep[head[b]]) swap(a, b);
    return dep[a] < dep[b] ? a : b;
  }
  pii subtree(int v) { return {pos[v], pos[v] + sub[v]}; }
};
