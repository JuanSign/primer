ll floorSum(ll n, ll m, ll a, ll b) {
  ll r = 0;
  if (a < 0) {
    ll a2 = a % m + m;
    r -= n * (n - 1) / 2 * ((a2 - a) / m), a = a2;
  }
  if (b < 0) {
    ll b2 = b % m + m;
    r -= n * ((b2 - b) / m), b = b2;
  }
  while (1) {
    if (a >= m) r += n * (n - 1) / 2 * (a / m), a %= m;
    if (b >= m) r += n * (b / m), b %= m;
    ll y = a * n + b;
    if (y < m) break;
    n = y / m, b = y % m, swap(m, a);
  }
  return r;
}
