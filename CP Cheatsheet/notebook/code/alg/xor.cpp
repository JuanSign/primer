struct XorBasis {
  ll b[62] = {};
  bool insert(ll x) {
    for (int i = 61; i >= 0; i--) if (x >> i & 1) {
      if (!b[i]) return b[i] = x, 1;
      x ^= b[i];
    }
    return 0;
  }
  ll maxXor(ll x = 0) {
    for (int i = 61; i >= 0; i--) x = max(x, x ^ b[i]);
    return x;
  }
};
typedef bitset<2048> bs;
int gaussXor(vector<bs>& a, int m) {
  int r = 0;
  rep(c, 0, m) {
    int p = r;
    while (p < sz(a) && !a[p][c]) p++;
    if (p == sz(a)) continue;
    swap(a[p], a[r]);
    rep(i, 0, sz(a)) if (i != r && a[i][c]) a[i] ^= a[r];
    if (++r == sz(a)) break;
  }
  rep(i, r, sz(a)) if (a[i][m]) return -1;
  return r;
}
