bool half(P p) { return p.y < 0 || (p.y == 0 && p.x < 0); }
bool angleLess(P a, P b) {
  if (half(a) != half(b)) return half(a) < half(b);
  return a.cross(b) > 0;
}
vector<P> minkowski(vector<P> a, vector<P> b) {
  auto fix = [](vector<P>& v) {
    rotate(v.begin(), min_element(all(v), [](P p, P q) {
      return tie(p.y, p.x) < tie(q.y, q.x);
    }), v.end());
    v.push_back(v[0]), v.push_back(v[1]);
  };
  fix(a), fix(b);
  vector<P> r;
  int i = 0, j = 0, n = sz(a) - 2, m = sz(b) - 2;
  while (i < n || j < m) {
    r.push_back(a[i] + b[j]);
    ll c = (a[i + 1] - a[i]).cross(b[j + 1] - b[j]);
    if (c >= 0 && i < n) i++;
    if (c <= 0 && j < m) j++;
  }
  return r;
}
