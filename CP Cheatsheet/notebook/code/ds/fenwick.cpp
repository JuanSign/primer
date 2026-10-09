struct FenwickTree {
  int n;
  vector<ll> t;
  FenwickTree(int N) : n(N), t(N + 1) {}
  FenwickTree(const vector<ll>& a) : FenwickTree(sz(a)) {
    rep(i, 0, n) add(i, a[i]);
  }
  void add(int i, ll x) { // a[i] += x
    for (i++; i <= n; i += i & -i) t[i] += x;
  }
  ll sum(int r) { // a[0] + ... + a[r - 1]
    ll s = 0;
    for (; r > 0; r -= r & -r) s += t[r];
    return s;
  }
  ll query(int l, int r) { return sum(r) - sum(l); }
};
