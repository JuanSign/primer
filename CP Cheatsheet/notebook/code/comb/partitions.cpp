vector<ll> partitions(int n) {
  vector<ll> p(n + 1);
  p[0] = 1;
  rep(i, 1, n + 1) for (int k = 1;; k++) {
    int a = k * (3 * k - 1) / 2, b = a + k;
    if (a > i) break;
    ll s = p[i - a] + (b <= i ? p[i - b] : 0);
    p[i] = (p[i] + (k & 1 ? s : MOD - s % MOD)) % MOD;
  }
  return p;
}
