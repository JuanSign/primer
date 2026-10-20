typedef unsigned long long ull;
const ull M = (1ULL << 61) - 1;
ull mul(ull a, ull b) {
  __uint128_t c = (__uint128_t)a * b;
  ull r = ull(c & M) + ull(c >> 61);
  return r >= M ? r - M : r;
}
struct Hash {
  vector<ull> h, p;
  Hash(const string& s, ull B)
      : h(sz(s) + 1), p(sz(s) + 1, 1) {
    rep(i, 0, sz(s)) {
      h[i + 1] = (mul(h[i], B) + s[i]) % M;
      p[i + 1] = mul(p[i], B);
    }
  }
  ull get(int l, int r) {
    return (h[r] + M - mul(h[l], p[r - l])) % M;
  }
};
