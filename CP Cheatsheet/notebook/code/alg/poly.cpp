vl inv(const vl& a, int n) {
  vl b{modpow(a[0], mod - 2, mod)};
  for (int k = 1; k < n; k *= 2) {
    vl c(a.begin(), a.begin() + min(sz(a), 2 * k));
    c = conv(c, conv(b, b)), b.resize(2 * k);
    rep(i, 0, 2 * k)
      b[i] = (2 * b[i] - (i < sz(c) ? c[i] : 0) + mod) % mod;
  }
  b.resize(n);
  return b;
}
vl deriv(vl a) {
  rep(i, 1, sz(a)) a[i - 1] = a[i] * i % mod;
  if (sz(a)) a.pop_back();
  return a;
}
vl integ(vl a) {
  a.push_back(0);
  for (int i = sz(a) - 1; i; i--)
    a[i] = a[i - 1] * modpow(i, mod - 2, mod) % mod;
  a[0] = 0;
  return a;
}
vl log(const vl& a, int n) {
  vl r = conv(deriv(a), inv(a, n));
  r.resize(n - 1);
  return integ(r);
}
vl exp(const vl& a, int n) {
  vl b{1};
  for (int k = 1; k < n; k *= 2) {
    vl l = log(b, 2 * k);
    rep(i, 0, 2 * k)
      l[i] = ((i < sz(a) ? a[i] : 0) - l[i] + mod) % mod;
    l[0] = (l[0] + 1) % mod;
    b = conv(b, l), b.resize(2 * k);
  }
  b.resize(n);
  return b;
}
