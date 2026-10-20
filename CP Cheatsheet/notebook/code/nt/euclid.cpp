ll euclid(ll a, ll b, ll& x, ll& y) {
  if (!b) return x = 1, y = 0, a;
  ll d = euclid(b, a % b, y, x);
  return y -= a / b * x, d;
}
ll modinv(ll a, ll m) {
  ll x, y;
  return euclid(a, m, x, y) == 1 ? (x % m + m) % m : -1;
}
pair<ll, ll> crt(ll a, ll m, ll b, ll n) {
  if (n > m) swap(a, b), swap(m, n);
  ll x, y, g = euclid(m, n, x, y), l = m / g * n;
  if ((a - b) % g) return {-1, -1};
  x = (b - a) % n * x % n / g * m + a;
  return {x < 0 ? x + l : x, l};
}
