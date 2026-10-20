template<class F> double simpson(F f, double a, double b,
                                 int n = 1000) {
  double h = (b - a) / n, s = f(a) + f(b);
  rep(i, 1, n) s += f(a + i * h) * (i & 1 ? 4 : 2);
  return s * h / 3;
}
template<class F> double ternary(F f, double lo, double hi) {
  rep(it, 0, 200) {
    double m1 = lo + (hi - lo) / 3, m2 = hi - (hi - lo) / 3;
    if (f(m1) < f(m2)) hi = m2;
    else lo = m1;
  }
  return lo;
}
