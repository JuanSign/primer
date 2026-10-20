struct Fenwick2D {
  int n, m;
  vector<vector<ll>> t;
  Fenwick2D(int N, int M)
      : n(N), m(M), t(N + 1, vector<ll>(M + 1)) {}
  void add(int x, int y, ll v) {
    for (int i = x + 1; i <= n; i += i & -i)
      for (int j = y + 1; j <= m; j += j & -j) t[i][j] += v;
  }
  ll sum(int x, int y) {
    ll s = 0;
    for (int i = x; i > 0; i -= i & -i)
      for (int j = y; j > 0; j -= j & -j) s += t[i][j];
    return s;
  }
  ll query(int x1, int y1, int x2, int y2) {
    return sum(x2, y2) - sum(x1, y2) - sum(x2, y1) +
           sum(x1, y1);
  }
};
