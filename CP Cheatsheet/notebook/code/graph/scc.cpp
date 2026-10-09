// comp[v] = SCC of v, k = number of SCCs. Each edge a -> b has
// comp[a] >= comp[b], so ids are a reverse topological order.
struct SCC {
  const vector<vi>& g;
  vi num, low, comp, st;
  int t = 0, k = 0;
  SCC(const vector<vi>& G)
      : g(G), num(sz(G), -1), low(sz(G)), comp(sz(G), -1) {
    rep(v, 0, sz(g)) if (num[v] < 0) dfs(v);
  }
  void dfs(int v) {
    num[v] = low[v] = t++;
    st.push_back(v);
    for (int u : g[v]) {
      if (num[u] < 0) dfs(u), low[v] = min(low[v], low[u]);
      else if (comp[u] < 0) low[v] = min(low[v], num[u]);
    }
    if (low[v] < num[v]) return;
    int u;
    do u = st.back(), st.pop_back(), comp[u] = k;
    while (u != v);
    k++;
  }
};
