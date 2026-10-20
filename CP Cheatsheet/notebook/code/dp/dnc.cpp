vector<ll> prv, cur;
ll cost(int k, int i);
void solve(int l, int r, int optl, int optr) {
  if (l >= r) return;
  int m = (l + r) / 2;
  pair<ll, int> best{LLONG_MAX / 4, optl};
  rep(k, optl, min(m - 1, optr) + 1)
    best = min(best, {prv[k] + cost(k, m), k});
  cur[m] = best.first;
  solve(l, m, optl, best.second);
  solve(m + 1, r, best.second, optr);
}
