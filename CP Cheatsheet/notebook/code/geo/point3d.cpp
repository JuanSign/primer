template<class T> struct Point3D {
  typedef Point3D P;
  typedef const P& R;
  T x, y, z;
  explicit Point3D(T x = 0, T y = 0, T z = 0) : x(x), y(y), z(z) {}
  bool operator<(R p) const { return tie(x, y, z) < tie(p.x, p.y, p.z); }
  bool operator==(R p) const { return tie(x, y, z) == tie(p.x, p.y, p.z); }
  P operator+(R p) const { return P(x + p.x, y + p.y, z + p.z); }
  P operator-(R p) const { return P(x - p.x, y - p.y, z - p.z); }
  P operator*(T d) const { return P(x * d, y * d, z * d); }
  P operator/(T d) const { return P(x / d, y / d, z / d); }
  T dot(R p) const { return x * p.x + y * p.y + z * p.z; }
  P cross(R p) const { return P(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x); }
  T dist2() const { return x * x + y * y + z * z; }
  double dist() const { return sqrt((double)dist2()); }
  P unit() const { return *this / (T)dist(); }
};
typedef Point3D<double> P3;
struct PR {
  void ins(int x) { (a == -1 ? a : b) = x; }
  void rem(int x) { (a == x ? a : b) = -1; }
  int cnt() { return (a != -1) + (b != -1); }
  int a, b;
};
struct F { P3 q; int a, b, c; };
vector<F> hull3d(const vector<P3>& A) {
  vector<vector<PR>> E(sz(A), vector<PR>(sz(A), {-1, -1}));
#define E(x, y) E[f.x][f.y]
  vector<F> FS;
  auto mf = [&](int i, int j, int k, int l) {
    P3 q = (A[j] - A[i]).cross((A[k] - A[i]));
    if (q.dot(A[l]) > q.dot(A[i])) q = q * -1;
    F f{q, i, j, k};
    E(a, b).ins(k), E(a, c).ins(j), E(b, c).ins(i);
    FS.push_back(f);
  };
  rep(i, 0, 4) rep(j, i + 1, 4) rep(k, j + 1, 4) mf(i, j, k, 6 - i - j - k);
  rep(i, 4, sz(A)) {
    rep(j, 0, sz(FS)) {
      F f = FS[j];
      if (f.q.dot(A[i]) > f.q.dot(A[f.a])) {
        E(a, b).rem(f.c), E(a, c).rem(f.b), E(b, c).rem(f.a);
        swap(FS[j--], FS.back());
        FS.pop_back();
      }
    }
    int nw = sz(FS);
    rep(j, 0, nw) {
      F f = FS[j];
#define C(a, b, c) if (E(a, b).cnt() != 2) mf(f.a, f.b, i, f.c);
      C(a, b, c); C(a, c, b); C(b, c, a);
    }
  }
  for (F& it : FS)
    if ((A[it.b] - A[it.a]).cross(A[it.c] - A[it.a]).dot(it.q) <= 0) swap(it.c, it.b);
  return FS;
}
double volume(const vector<P3>& A, const vector<F>& fs) {
  double v = 0;
  for (auto& f : fs) v += A[f.a].dot(A[f.b].cross(A[f.c]));
  return v / 6;
}
