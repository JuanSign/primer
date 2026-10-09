struct SegTree {
  typedef ll T; // node value
  typedef ll L; // lazy tag
  T e = 0;      // merge identity
  L id = 0;     // tag that changes nothing
  T merge(T a, T b) { return a + b; }
  T apply(T x, L f, int len) { return x + f * len; }
  L comp(L f, L g) { return f + g; } // f applied after g

  int n;
  vector<T> t;
  vector<L> lz;
  SegTree(int N) : n(N), t(4 * N, e), lz(4 * N, id) {}
  SegTree(const vector<T>& a) : SegTree(sz(a)) {
    build(a, 1, 0, n);
  }
  void build(const vector<T>& a, int v, int lo, int hi) {
    if (hi - lo == 1) { t[v] = a[lo]; return; }
    int m = (lo + hi) / 2;
    build(a, 2 * v, lo, m), build(a, 2 * v + 1, m, hi);
    t[v] = merge(t[2 * v], t[2 * v + 1]);
  }
  void put(int v, int len, L f) {
    t[v] = apply(t[v], f, len), lz[v] = comp(f, lz[v]);
  }
  void push(int v, int lo, int m, int hi) {
    put(2 * v, m - lo, lz[v]), put(2 * v + 1, hi - m, lz[v]);
    lz[v] = id;
  }

  void update(int l, int r, L f) { update(l, r, f, 1, 0, n); }
  void update(int l, int r, L f, int v, int lo, int hi) {
    if (r <= lo || hi <= l) return;
    if (l <= lo && hi <= r) return put(v, hi - lo, f);
    int m = (lo + hi) / 2;
    push(v, lo, m, hi);
    update(l, r, f, 2 * v, lo, m);
    update(l, r, f, 2 * v + 1, m, hi);
    t[v] = merge(t[2 * v], t[2 * v + 1]);
  }

  T query(int l, int r) { return query(l, r, 1, 0, n); }
  T query(int l, int r, int v, int lo, int hi) {
    if (r <= lo || hi <= l) return e;
    if (l <= lo && hi <= r) return t[v];
    int m = (lo + hi) / 2;
    push(v, lo, m, hi);
    return merge(query(l, r, 2 * v, lo, m),
                 query(l, r, 2 * v + 1, m, hi));
  }

  void set(int i, T x) { set(i, x, 1, 0, n); }
  void set(int i, T x, int v, int lo, int hi) {
    if (hi - lo == 1) { t[v] = x; return; }
    int m = (lo + hi) / 2;
    push(v, lo, m, hi);
    if (i < m) set(i, x, 2 * v, lo, m);
    else set(i, x, 2 * v + 1, m, hi);
    t[v] = merge(t[2 * v], t[2 * v + 1]);
  }

  // smallest i >= l with f(query(l, i + 1)), else n
  template<class F> int first(int l, F f) {
    T acc = e;
    return first(l, f, acc, 1, 0, n);
  }
  template<class F>
  int first(int l, F& f, T& acc, int v, int lo, int hi) {
    if (hi <= l) return n;
    if (l <= lo) {
      T s = merge(acc, t[v]);
      if (!f(s)) { acc = s; return n; }
      if (hi - lo == 1) return lo;
    }
    int m = (lo + hi) / 2;
    push(v, lo, m, hi);
    int i = first(l, f, acc, 2 * v, lo, m);
    return i < n ? i : first(l, f, acc, 2 * v + 1, m, hi);
  }
};
