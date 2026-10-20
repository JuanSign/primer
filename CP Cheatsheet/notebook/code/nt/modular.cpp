ll modpow(ll b, ll e, ll m) {
  ll r = 1;
  for (b %= m; e; e >>= 1, b = b * b % m)
    if (e & 1) r = r * b % m;
  return r;
}
const ll MOD = 998244353;
struct Mint {
  ll v;
  Mint(ll x = 0) : v((x % MOD + MOD) % MOD) {}
  friend Mint operator+(Mint a, Mint b) { return a.v + b.v; }
  friend Mint operator-(Mint a, Mint b) { return a.v - b.v; }
  friend Mint operator*(Mint a, Mint b) { return a.v * b.v; }
  friend Mint operator/(Mint a, Mint b) { return a * b.inv(); }
  Mint inv() const { return modpow(v, MOD - 2, MOD); }
};
