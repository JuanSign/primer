pair<ll, vi> globalMinCut(vector<vector<ll>> mat) {
  pair<ll, vi> best = {LLONG_MAX, {}};
  int n = sz(mat);
  vector<vi> co(n);
  rep(i, 0, n) co[i] = {i};
  rep(ph, 1, n) {
    vector<ll> w = mat[0];
    int s = 0, t = 0;
    rep(it, 0, n - ph) {
      w[t] = LLONG_MIN;
      s = t, t = max_element(all(w)) - w.begin();
      rep(i, 0, n) w[i] += mat[t][i];
    }
    best = min(best, {w[t] - mat[t][t], co[t]});
    co[s].insert(co[s].end(), all(co[t]));
    rep(i, 0, n) mat[s][i] += mat[t][i];
    rep(i, 0, n) mat[i][s] = mat[s][i];
    mat[0][t] = LLONG_MIN;
  }
  return best;
}
