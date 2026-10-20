vector<PD> circleLine(PD c, double r, PD a, PD b) {
  PD ab = b - a, p = a + ab * (c - a).dot(ab) / ab.dist2();
  double s = a.cross(b, c), h2 = r * r - s * s / ab.dist2();
  if (h2 < 0) return {};
  if (h2 == 0) return {p};
  PD h = ab.unit() * sqrt(h2);
  return {p - h, p + h};
}
bool circleInter(PD a, PD b, double r1, double r2, pair<PD, PD>* out) {
  if (a == b) return false;
  PD vec = b - a;
  double d2 = vec.dist2(), sum = r1 + r2, dif = r1 - r2;
  double p = (d2 + r1 * r1 - r2 * r2) / (d2 * 2), h2 = r1 * r1 - p * p * d2;
  if (sum * sum < d2 || dif * dif > d2) return false;
  PD mid = a + vec * p, per = vec.perp() * sqrt(fmax(0, h2) / d2);
  *out = {mid + per, mid - per};
  return true;
}
vector<pair<PD, PD>> tangents(PD c1, double r1, PD c2, double r2) {
  PD d = c2 - c1;
  double dr = r1 - r2, d2 = d.dist2(), h2 = d2 - dr * dr;
  if (d2 == 0 || h2 < 0) return {};
  vector<pair<PD, PD>> out;
  for (double sg : {-1, 1}) {
    PD v = (d * dr + d.perp() * sqrt(h2) * sg) / d2;
    out.push_back({c1 + v * r1, c2 + v * r2});
  }
  if (h2 == 0) out.pop_back();
  return out;
}
PD ccCenter(PD A, PD B, PD C) {
  PD b = C - A, c = B - A;
  return A + (b * c.dist2() - c * b.dist2()).perp() / b.cross(c) / 2;
}
pair<PD, double> mec(vector<PD> ps) {
  shuffle(all(ps), mt19937(time(0)));
  PD o = ps[0];
  double r = 0, EPS = 1 + 1e-8;
  rep(i, 0, sz(ps)) if ((o - ps[i]).dist() > r * EPS) {
    o = ps[i], r = 0;
    rep(j, 0, i) if ((o - ps[j]).dist() > r * EPS) {
      o = (ps[i] + ps[j]) / 2, r = (o - ps[i]).dist();
      rep(k, 0, j) if ((o - ps[k]).dist() > r * EPS)
        o = ccCenter(ps[i], ps[j], ps[k]), r = (o - ps[i]).dist();
    }
  }
  return {o, r};
}
#define arg(p, q) atan2(p.cross(q), p.dot(q))
double circlePoly(PD c, double r, vector<PD> ps) {
  auto tri = [&](PD p, PD q) {
    auto r2 = r * r / 2;
    PD d = q - p;
    auto a = d.dot(p) / d.dist2(), b = (p.dist2() - r * r) / d.dist2();
    auto det = a * a - b;
    if (det <= 0) return arg(p, q) * r2;
    auto s = max(0., -a - sqrt(det)), t = min(1., -a + sqrt(det));
    if (t < 0 || 1 <= s) return arg(p, q) * r2;
    PD u = p + d * s, v = p + d * t;
    return arg(p, u) * r2 + u.cross(v) / 2 + arg(v, q) * r2;
  };
  double sum = 0;
  rep(i, 0, sz(ps)) sum += tri(ps[i] - c, ps[(i + 1) % sz(ps)] - c);
  return sum;
}
