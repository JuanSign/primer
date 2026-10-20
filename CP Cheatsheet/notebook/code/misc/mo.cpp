void add(int i, int end);
void del(int i, int end);
ll calc();
vector<ll> mo(vector<pii> Q) {
  int L = 0, R = 0, blk = 350;
  vi s(sz(Q));
  vector<ll> res(sz(Q));
#define K(x) \
  pii(x.first / blk, x.second ^ -(x.first / blk & 1))
  iota(all(s), 0);
  sort(all(s), [&](int a, int b) {
    return K(Q[a]) < K(Q[b]);
  });
  for (int qi : s) {
    auto [l, r] = Q[qi];
    while (L > l) add(--L, 0);
    while (R < r) add(R++, 1);
    while (L < l) del(L++, 0);
    while (R > r) del(--R, 1);
    res[qi] = calc();
  }
  return res;
}
