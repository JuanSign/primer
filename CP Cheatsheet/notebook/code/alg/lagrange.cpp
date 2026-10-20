ll lagrange(const vector<ll>& y, ll x) {
  int n = sz(y);
  x %= MOD;
  vector<ll> pre(n + 1, 1), suf(n + 1, 1), f(n, 1);
  rep(i, 0, n)
    pre[i + 1] = pre[i] * ((x - i + MOD) % MOD) % MOD;
  for (int i = n; i--;)
    suf[i] = suf[i + 1] * ((x - i + MOD) % MOD) % MOD;
  rep(i, 1, n) f[i] = f[i - 1] * i % MOD;
  ll r = 0;
  rep(i, 0, n) {
    ll d = f[i] * f[n - 1 - i] % MOD;
    ll t = y[i] % MOD * pre[i] % MOD * suf[i + 1] % MOD *
           modpow(d, MOD - 2, MOD) % MOD;
    r = (r + ((n - 1 - i) & 1 ? MOD - t : t)) % MOD;
  }
  return r;
}
