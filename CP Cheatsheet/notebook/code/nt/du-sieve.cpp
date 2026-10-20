// Mertens: start r = 1 instead of n(n + 1) / 2
vector<ll> pre;
unordered_map<ll, ll> memo;
ll phiSum(ll n) {
  if (n < sz(pre)) return pre[n];
  if (memo.count(n)) return memo[n];
  ll r = n % MOD * ((n + 1) % MOD) % MOD * ((MOD + 1) / 2) %
         MOD;
  for (ll l = 2, h; l <= n; l = h + 1) {
    h = n / (n / l);
    r = (r - (h - l + 1) % MOD * phiSum(n / l)) % MOD;
  }
  return memo[n] = (r + MOD) % MOD;
}
