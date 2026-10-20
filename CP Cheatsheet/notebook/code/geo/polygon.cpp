template<class T> T polygonArea2(const vector<Point<T>>& v) {
  T a = v.back().cross(v[0]);
  rep(i, 0, sz(v) - 1) a += v[i].cross(v[i + 1]);
  return a;
}
template<class P>
bool inPolygon(const vector<P>& p, P a, bool strict = true) {
  int cnt = 0, n = sz(p);
  rep(i, 0, n) {
    P q = p[(i + 1) % n];
    if (onSegment(p[i], q, a)) return !strict;
    cnt ^= ((a.y < p[i].y) - (a.y < q.y)) *
               a.cross(p[i], q) > 0;
  }
  return cnt;
}
typedef Point<double> PD;
PD polygonCenter(const vector<PD>& v) {
  PD res(0, 0);
  double A = 0;
  for (int i = 0, j = sz(v) - 1; i < sz(v); j = i++) {
    res = res + (v[i] + v[j]) * v[j].cross(v[i]);
    A += v[j].cross(v[i]);
  }
  return res / A / 3;
}
vector<PD> polygonCut(const vector<PD>& poly, PD s, PD e) {
  vector<PD> res;
  rep(i, 0, sz(poly)) {
    PD cur = poly[i], prev = i ? poly[i - 1] : poly.back();
    auto a = s.cross(e, cur), b = s.cross(e, prev);
    if ((a < 0) != (b < 0))
      res.push_back(cur + (prev - cur) * (a / (a - b)));
    if (a < 0) res.push_back(cur);
  }
  return res;
}
