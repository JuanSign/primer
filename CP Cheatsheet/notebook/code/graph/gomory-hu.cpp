typedef array<ll, 3> Edge;
vector<Edge> gomoryHu(int n, const vector<Edge>& ed) {
  vector<Edge> tree;
  vi par(n);
  rep(i, 1, n) {
    Dinic D(n);
    for (auto [a, b, c] : ed) D.addEdge(a, b, c, c);
    tree.push_back({i, par[i], D.calc(i, par[i])});
    rep(j, i + 1, n)
      if (par[j] == par[i] && D.leftOfMinCut(j)) par[j] = i;
  }
  return tree;
}
