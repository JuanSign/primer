struct SparseTable {
  typedef pii T; // {a[i], i}, min gives leftmost argmin
  T op(T a, T b) { return min(a, b); } // needs op(x, x) == x
  vector<vector<T>> t; // t[k][i] = op of [i, i + 2^k)
  SparseTable(const vector<T>& a) : t(1, a) {
    for (int k = 1; (1 << k) <= sz(a); k++) {
      int h = 1 << (k - 1);
      t.emplace_back(sz(a) - 2 * h + 1);
      rep(i, 0, sz(t[k]))
        t[k][i] = op(t[k - 1][i], t[k - 1][i + h]);
    }
  }
  T query(int l, int r) { // needs l < r
    int k = __lg(r - l);
    return op(t[k][l], t[k][r - (1 << k)]);
  }
};
