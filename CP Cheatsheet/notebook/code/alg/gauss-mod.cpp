// Ax = b: rows [A|b], rref(a, m) = r, none if some row >= r
// has a[i][m] != 0, else x[pivot col] = a[row][m].
// Inverse: rows [A|I], rref(a, n) == n leaves A^-1 right.
int rref(vector<vector<ll>>& a, int m) {
  int n = sz(a), r = 0;
  rep(c, 0, m) {
    int p = r;
    while (p < n && !a[p][c]) p++;
    if (p == n) continue;
    swap(a[p], a[r]);
    ll iv = modpow(a[r][c], MOD - 2, MOD);
    for (ll& v : a[r]) v = v * iv % MOD;
    rep(i, 0, n) if (i != r && a[i][c]) {
      ll f = a[i][c];
      rep(j, 0, sz(a[r]))
        a[i][j] = (a[i][j] - f * a[r][j] % MOD + MOD) % MOD;
    }
    if (++r == n) break;
  }
  return r;
}
ll det(vector<vector<ll>> a, ll mod) {
  int n = sz(a);
  ll ans = 1;
  rep(i, 0, n) {
    rep(j, i + 1, n) while (a[j][i] != 0) {
      ll t = a[i][i] / a[j][i];
      if (t) rep(k, i, n)
        a[i][k] = (a[i][k] - a[j][k] * t) % mod;
      swap(a[i], a[j]), ans *= -1;
    }
    ans = ans * a[i][i] % mod;
    if (!ans) return 0;
  }
  return (ans + mod) % mod;
}
