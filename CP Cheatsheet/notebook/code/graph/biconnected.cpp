// undirected, multi-edges ok. blocks = vertex biconnected
// components, an isolated vertex is one on its own.
// block-cut tree: join v and n + i for every v in blocks[i]
struct Biconnected {
  vector<vector<pii>> g; // {neighbor, edge id}
  vi num, low, cut, bridge, st;
  vector<vi> blocks;
  int t = 0;
  Biconnected(int n) : g(n), num(n, -1), low(n), cut(n) {}
  void addEdge(int a, int b) {
    g[a].push_back({b, sz(bridge)});
    g[b].push_back({a, sz(bridge)});
    bridge.push_back(0);
  }
  void run() {
    rep(v, 0, sz(g)) if (num[v] < 0) {
      dfs(v, -1), st.pop_back();
      if (g[v].empty()) blocks.push_back({v});
    }
  }
  void dfs(int v, int pe) {
    num[v] = low[v] = t++;
    st.push_back(v);
    int kids = 0;
    for (auto [u, e] : g[v]) {
      if (e == pe) continue;
      if (num[u] >= 0) {
        low[v] = min(low[v], num[u]);
        continue;
      }
      dfs(u, e), kids++;
      low[v] = min(low[v], low[u]);
      if (low[u] > num[v]) bridge[e] = 1;
      if (low[u] < num[v]) continue;
      if (pe >= 0 || kids > 1) cut[v] = 1;
      vi b{v};
      int w;
      do w = st.back(), st.pop_back(), b.push_back(w);
      while (w != u);
      blocks.push_back(b);
    }
  }
  vi twoEdge() { // 2-edge-connected component of each vertex
    vi c(sz(g), -1);
    int k = 0;
    rep(s, 0, sz(g)) if (c[s] < 0) {
      vi q{s};
      c[s] = k;
      rep(i, 0, sz(q)) for (auto [u, e] : g[q[i]])
        if (!bridge[e] && c[u] < 0) c[u] = k, q.push_back(u);
      k++;
    }
    return c;
  }
};
