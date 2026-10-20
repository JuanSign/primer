vi dominators(const vector<vi>& g, int s) {
  int n = sz(g), t = 0;
  vector<vi> rg(n), bucket(n);
  vi num(n, -1), ord, par(n), sdom(n), idom(n, -1), dsu(n),
      best(n);
  rep(v, 0, n) for (int u : g[v]) rg[u].push_back(v);
  function<void(int)> dfs = [&](int v) {
    num[v] = t++, ord.push_back(v);
    for (int u : g[v]) if (num[u] < 0) par[u] = v, dfs(u);
  };
  dfs(s);
  iota(all(dsu), 0), iota(all(best), 0);
  rep(v, 0, n) sdom[v] = num[v];
  function<int(int)> find = [&](int v) {
    if (dsu[v] == v) return v;
    int r = find(dsu[v]);
    if (sdom[best[dsu[v]]] < sdom[best[v]])
      best[v] = best[dsu[v]];
    dsu[v] = r;
    return r;
  };
  auto eval = [&](int v) { find(v); return best[v]; };
  for (int i = t - 1; i > 0; i--) {
    int w = ord[i];
    for (int u : rg[w]) if (num[u] >= 0)
      sdom[w] = min(sdom[w], sdom[eval(u)]);
    bucket[ord[sdom[w]]].push_back(w);
    dsu[w] = par[w];
    for (int v : bucket[par[w]]) {
      int u = eval(v);
      idom[v] = sdom[u] < sdom[v] ? u : par[w];
    }
    bucket[par[w]].clear();
  }
  rep(i, 1, t) {
    int w = ord[i];
    if (idom[w] != ord[sdom[w]]) idom[w] = idom[idom[w]];
  }
  idom[s] = s;
  return idom;
}
