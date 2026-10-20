void fwht(vector<ll>& a, int t, bool inv) {
  for (int n = sz(a), k = 1; k < n; k *= 2)
    for (int i = 0; i < n; i += 2 * k) rep(j, i, i + k) {
      ll &u = a[j], &v = a[j + k], x = u, y = v;
      if (t == 0) u = inv ? y - x : y, v = inv ? x : x + y;
      if (t == 1) u = inv ? y : x + y, v = inv ? x - y : x;
      if (t == 2) u = x + y, v = x - y;
    }
  if (inv && t == 2) for (ll& x : a) x /= sz(a);
}
vector<ll> conv(vector<ll> a, vector<ll> b, int t) {
  fwht(a, t, 0), fwht(b, t, 0);
  rep(i, 0, sz(a)) a[i] *= b[i];
  fwht(a, t, 1);
  return a;
}
