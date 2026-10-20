ll primitiveRoot(ll p) {
  vector<ll> f;
  ll n = p - 1;
  for (ll i = 2; i * i <= n; i++)
    if (n % i == 0) {
      f.push_back(i);
      while (n % i == 0) n /= i;
    }
  if (n > 1) f.push_back(n);
  for (ll g = 1;; g++) {
    bool ok = 1;
    for (ll q : f) ok &= modpow(g, (p - 1) / q, p) != 1;
    if (ok) return g;
  }
}
