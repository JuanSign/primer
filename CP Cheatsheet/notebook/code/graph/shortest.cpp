vector<ll> dijkstra(const vector<vector<pair<int, ll>>>& g,
                    int s) {
  vector<ll> d(sz(g), LLONG_MAX);
  priority_queue<pair<ll, int>> pq;
  pq.push({d[s] = 0, s});
  while (!pq.empty()) {
    auto [w, v] = pq.top();
    pq.pop();
    if (-w != d[v]) continue;
    for (auto [u, c] : g[v])
      if (d[v] + c < d[u]) pq.push({-(d[u] = d[v] + c), u});
  }
  return d;
}
void floyd(vector<vector<ll>>& d) {
  int n = sz(d);
  const ll inf = LLONG_MAX / 4;
  rep(i, 0, n) d[i][i] = min(d[i][i], 0LL);
  rep(k, 0, n) rep(i, 0, n) rep(j, 0, n)
    if (d[i][k] < inf && d[k][j] < inf)
      d[i][j] = min(d[i][j], max(d[i][k] + d[k][j], -inf));
  rep(k, 0, n) if (d[k][k] < 0) rep(i, 0, n) rep(j, 0, n)
    if (d[i][k] < inf && d[k][j] < inf) d[i][j] = -inf;
}
vi topoSort(const vector<vi>& g) {
  vi in(sz(g)), q;
  for (auto& v : g) for (int u : v) in[u]++;
  rep(v, 0, sz(g)) if (!in[v]) q.push_back(v);
  rep(i, 0, sz(q)) for (int u : g[q[i]])
    if (!--in[u]) q.push_back(u);
  return q;
}
