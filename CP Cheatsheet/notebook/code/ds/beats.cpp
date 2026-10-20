struct Beats {
  struct N { ll mx, mx2, cnt, sum; };
  int n;
  vector<N> t;
  Beats(const vector<ll>& a) : n(sz(a)), t(4 * sz(a)) {
    build(a, 1, 0, n);
  }
  void pull(int v) {
    N &l = t[2 * v], &r = t[2 * v + 1], &x = t[v];
    x.sum = l.sum + r.sum, x.mx = max(l.mx, r.mx);
    x.mx2 = max(l.mx == x.mx ? l.mx2 : l.mx,
                r.mx == x.mx ? r.mx2 : r.mx);
    x.cnt = (l.mx == x.mx ? l.cnt : 0) +
            (r.mx == x.mx ? r.cnt : 0);
  }
  void build(const vector<ll>& a, int v, int lo, int hi) {
    if (hi - lo == 1) {
      t[v] = {a[lo], LLONG_MIN, 1, a[lo]};
      return;
    }
    int m = (lo + hi) / 2;
    build(a, 2 * v, lo, m), build(a, 2 * v + 1, m, hi);
    pull(v);
  }
  void put(int v, ll x) {
    if (x >= t[v].mx) return;
    t[v].sum -= (t[v].mx - x) * t[v].cnt, t[v].mx = x;
  }
  void push(int v) {
    put(2 * v, t[v].mx), put(2 * v + 1, t[v].mx);
  }
  void chmin(int l, int r, ll x, int v, int lo, int hi) {
    if (r <= lo || hi <= l || t[v].mx <= x) return;
    if (l <= lo && hi <= r && t[v].mx2 < x) return put(v, x);
    push(v);
    int m = (lo + hi) / 2;
    chmin(l, r, x, 2 * v, lo, m);
    chmin(l, r, x, 2 * v + 1, m, hi);
    pull(v);
  }
  pair<ll, ll> query(int l, int r, int v, int lo, int hi) {
    if (r <= lo || hi <= l) return {0, LLONG_MIN};
    if (l <= lo && hi <= r) return {t[v].sum, t[v].mx};
    push(v);
    int m = (lo + hi) / 2;
    auto a = query(l, r, 2 * v, lo, m);
    auto b = query(l, r, 2 * v + 1, m, hi);
    return {a.first + b.first, max(a.second, b.second)};
  }
  void chmin(int l, int r, ll x) { chmin(l, r, x, 1, 0, n); }
  pair<ll, ll> query(int l, int r) {
    return query(l, r, 1, 0, n);
  }
};
