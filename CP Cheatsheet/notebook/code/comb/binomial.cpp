struct Binom {
  vector<ll> f, fi;
  Binom(int n) : f(n + 1, 1), fi(n + 1) {
    rep(i, 1, n + 1) f[i] = f[i - 1] * i % MOD;
    fi[n] = modpow(f[n], MOD - 2, MOD);
    for (int i = n; i > 0; i--) fi[i - 1] = fi[i] * i % MOD;
  }
  ll C(int n, int k) {
    if (k < 0 || k > n) return 0;
    return f[n] * fi[k] % MOD * fi[n - k] % MOD;
  }
};
ll lucas(ll n, ll k, ll p) {
  ll r = 1;
  for (; k; n /= p, k /= p) {
    ll a = n % p, b = k % p, num = 1, den = 1;
    if (b > a) return 0;
    rep(i, 0, b)
      num = num * (a - i) % p, den = den * (i + 1) % p;
    r = r * num % p * modpow(den, p - 2, p) % p;
  }
  return r;
}
