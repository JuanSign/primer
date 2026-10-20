ll steiner(const vector<vector<pair<int, ll>>>& g,
           const vi& t) {
  int n = sz(g), k = sz(t);
  const ll inf = LLONG_MAX / 4;
  vector<vector<ll>> dp(1 << k, vector<ll>(n, inf));
  rep(i, 0, k) dp[1 << i][t[i]] = 0;
  rep(m, 1, 1 << k) {
    auto& d = dp[m];
    rep(v, 0, n) for (int s = (m - 1) & m; s; s = (s - 1) & m)
      d[v] = min(d[v], dp[s][v] + dp[m ^ s][v]);
    priority_queue<pair<ll, int>> pq;
    rep(v, 0, n) if (d[v] < inf) pq.push({-d[v], v});
    while (!pq.empty()) {
      auto [w, v] = pq.top();
      pq.pop();
      if (-w != d[v]) continue;
      for (auto [u, c] : g[v])
        if (d[v] + c < d[u]) pq.push({-(d[u] = d[v] + c), u});
    }
  }
  return *min_element(all(dp.back()));
}
