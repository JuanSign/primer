const ll INF = LLONG_MAX;
vector<ll> bellmanFord(int n, const vector<array<ll, 3>>& ed,
                       int s) {
  vector<ll> d(n, INF);
  d[s] = 0;
  rep(i, 0, 2 * n) for (auto [a, b, w] : ed) {
    if (d[a] == INF) continue;
    ll nd = d[a] == -INF ? -INF : d[a] + w;
    if (nd < d[b]) d[b] = i < n - 1 ? nd : -INF;
  }
  return d;
}
