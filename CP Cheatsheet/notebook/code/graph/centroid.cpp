struct Centroid {
  const vector<vi>& g;
  vi sub, done, par;
  Centroid(const vector<vi>& G)
      : g(G), sub(sz(G)), done(sz(G)), par(sz(G), -1) {
    build(0, -1);
  }
  int size(int v, int p) {
    sub[v] = 1;
    for (int u : g[v])
      if (u != p && !done[u]) sub[v] += size(u, v);
    return sub[v];
  }
  void build(int v, int p) {
    int n = size(v, -1), q = -1;
    for (bool go = 1; go;) {
      go = 0;
      for (int u : g[v])
        if (u != q && !done[u] && 2 * sub[u] > n) {
          q = v, v = u, go = 1;
          break;
        }
    }
    done[v] = 1, par[v] = p;
    // v is the centroid: handle paths through v here
    for (int u : g[v]) if (!done[u]) build(u, v);
  }
};
