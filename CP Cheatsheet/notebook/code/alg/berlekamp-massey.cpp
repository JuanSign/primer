vector<ll> berlekampMassey(vector<ll> s) {
  int n = sz(s), L = 0, m = 0;
  vector<ll> C(n), B(n), T;
  C[0] = B[0] = 1;
  ll b = 1;
  rep(i, 0, n) {
    ++m;
    ll d = s[i] % MOD;
    rep(j, 1, L + 1) d = (d + C[j] * s[i - j]) % MOD;
    if (!d) continue;
    T = C;
    ll coef = d * modpow(b, MOD - 2, MOD) % MOD;
    rep(j, m, n) C[j] = (C[j] - coef * B[j - m]) % MOD;
    if (2 * L > i) continue;
    L = i + 1 - L, B = T, b = d, m = 0;
  }
  C.resize(L + 1), C.erase(C.begin());
  for (ll& x : C) x = (MOD - x) % MOD;
  return C;
}
ll linearRec(vector<ll> S, vector<ll> tr, ll k) {
  int n = sz(tr);
  auto combine = [&](vector<ll> a, vector<ll> b) {
    vector<ll> res(n * 2 + 1);
    rep(i, 0, n + 1) rep(j, 0, n + 1)
      res[i + j] = (res[i + j] + a[i] * b[j]) % MOD;
    for (int i = 2 * n; i > n; --i) rep(j, 0, n)
      res[i - 1 - j] = (res[i - 1 - j] + res[i] * tr[j]) % MOD;
    res.resize(n + 1);
    return res;
  };
  vector<ll> pol(n + 1), e(pol);
  pol[0] = e[1] = 1;
  for (++k; k; k /= 2) {
    if (k % 2) pol = combine(pol, e);
    e = combine(e, e);
  }
  ll res = 0;
  rep(i, 0, n) res = (res + pol[i + 1] * S[i]) % MOD;
  return res;
}
