struct HP {
  PD p, d;
  double a;
  HP(PD s, PD e) : p(s), d(e - s), a(atan2(d.y, d.x)) {}
  bool out(PD r) const { return d.cross(r - p) < -1e-9; }
};
PD inter(const HP& s, const HP& t) { return s.p + s.d * ((t.p - s.p).cross(t.d) / s.d.cross(t.d)); }
vector<PD> hpi(vector<HP> H) {
  sort(all(H), [](const HP& a, const HP& b) { return a.a < b.a; });
  deque<HP> q;
  for (auto& h : H) {
    while (sz(q) > 1 && h.out(inter(q.end()[-1], q.end()[-2]))) q.pop_back();
    while (sz(q) > 1 && h.out(inter(q[0], q[1]))) q.pop_front();
    if (sz(q) && fabs(h.d.cross(q.back().d)) < 1e-12) {
      if (h.d.dot(q.back().d) < 0) return {};
      if (!h.out(q.back().p)) continue;
      q.pop_back();
    }
    q.push_back(h);
  }
  while (sz(q) > 2 && q[0].out(inter(q.end()[-1], q.end()[-2]))) q.pop_back();
  while (sz(q) > 2 && q.back().out(inter(q[0], q[1]))) q.pop_front();
  if (sz(q) < 3) return {};
  vector<PD> r;
  rep(i, 0, sz(q)) r.push_back(inter(q[i], q[(i + 1) % sz(q)]));
  return r;
}
