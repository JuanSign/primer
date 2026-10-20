pair<ll, vi> hungarian(const vector<vector<ll>>& a) {
  if (a.empty()) return {0, {}};
  int n = sz(a) + 1, m = sz(a[0]) + 1;
  vector<ll> u(n), v(m);
  vi p(m), ans(n - 1);
  rep(i, 1, n) {
    p[0] = i;
    int j0 = 0;
    vector<ll> dist(m, LLONG_MAX);
    vi pre(m, -1);
    vector<bool> done(m + 1);
    do {
      done[j0] = 1;
      int i0 = p[j0], j1 = 0;
      ll delta = LLONG_MAX;
      rep(j, 1, m) if (!done[j]) {
        ll cur = a[i0 - 1][j - 1] - u[i0] - v[j];
        if (cur < dist[j]) dist[j] = cur, pre[j] = j0;
        if (dist[j] < delta) delta = dist[j], j1 = j;
      }
      rep(j, 0, m) {
        if (done[j]) u[p[j]] += delta, v[j] -= delta;
        else dist[j] -= delta;
      }
      j0 = j1;
    } while (p[j0]);
    while (j0) {
      int j1 = pre[j0];
      p[j0] = p[j1], j0 = j1;
    }
  }
  rep(j, 1, m) if (p[j]) ans[p[j] - 1] = j - 1;
  return {-v[0], ans};
}
