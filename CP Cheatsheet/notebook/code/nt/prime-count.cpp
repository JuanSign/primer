ll primeCount(ll n) {
  if (n < 2) return 0;
  ll r = sqrtl(n);
  while (r * r > n) r--;
  while ((r + 1) * (r + 1) <= n) r++;
  vector<ll> lo(r + 1), hi(r + 1);
  rep(i, 1, r + 1) lo[i] = i - 1, hi[i] = n / i - 1;
  for (ll p = 2; p <= r; p++) {
    if (lo[p] == lo[p - 1]) continue;
    ll c = lo[p - 1], p2 = p * p;
    for (ll i = 1; i <= r && n / i >= p2; i++) {
      ll d = i * p;
      hi[i] -= (d <= r ? hi[d] : lo[n / d]) - c;
    }
    for (ll i = r; i >= p2; i--) lo[i] -= lo[i / p] - c;
  }
  return hi[1];
}
