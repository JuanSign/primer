template<class P> int sideOf(P s, P e, P p) {
  return sgn(s.cross(e, p));
}
template<class P> bool onSegment(P s, P e, P p) {
  return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}
template<class P> double lineDist(P a, P b, P p) {
  return (double)(b - a).cross(p - a) / (b - a).dist();
}
template<class P> double segDist(P s, P e, P p) {
  if (s == e) return (p - s).dist();
  auto d = (e - s).dist2();
  auto t = min(d, max(.0, (p - s).dot(e - s)));
  return ((p - s) * d - (e - s) * t).dist() / d;
}
template<class P>
pair<int, P> lineInter(P s1, P e1, P s2, P e2) {
  auto d = (e1 - s1).cross(e2 - s2);
  if (d == 0) return {-(s1.cross(e1, s2) == 0), P(0, 0)};
  auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
  return {1, (s1 * p + e1 * q) / d};
}
template<class P> vector<P> segInter(P a, P b, P c, P d) {
  auto oa = c.cross(d, a), ob = c.cross(d, b),
       oc = a.cross(b, c), od = a.cross(b, d);
  if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0)
    return {(a * ob - b * oa) / (ob - oa)};
  set<P> s;
  if (onSegment(c, d, a)) s.insert(a);
  if (onSegment(c, d, b)) s.insert(b);
  if (onSegment(a, b, c)) s.insert(c);
  if (onSegment(a, b, d)) s.insert(d);
  return {all(s)};
}
template<class P> P project(P a, P b, P p) {
  P v = b - a;
  return a + v * (p - a).dot(v) / v.dist2();
}
template<class P> P reflect(P a, P b, P p) {
  return project(a, b, p) * 2 - p;
}
