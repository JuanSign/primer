typedef vector<vector<ll>> Mat;
Mat mul(const Mat& a, const Mat& b) {
  Mat c(sz(a), vector<ll>(sz(b[0])));
  rep(i, 0, sz(a)) rep(k, 0, sz(b)) if (a[i][k])
    rep(j, 0, sz(b[0]))
      c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % MOD;
  return c;
}
Mat mpow(Mat a, ll e) {
  Mat r(sz(a), vector<ll>(sz(a)));
  rep(i, 0, sz(a)) r[i][i] = 1;
  for (; e; e >>= 1, a = mul(a, a)) if (e & 1) r = mul(r, a);
  return r;
}
