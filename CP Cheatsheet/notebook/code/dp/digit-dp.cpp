// add a 'started' flag when leading zeros matter
string D;
int K;
ll memo[20][100];
ll go(int i, int s, bool tight) {
  if (i == sz(D)) return s == 0;
  ll& m = memo[i][s];
  if (!tight && m >= 0) return m;
  ll r = 0;
  int lim = tight ? D[i] - '0' : 9;
  rep(d, 0, lim + 1)
    r += go(i + 1, (s + d) % K, tight && d == lim);
  if (!tight) m = r;
  return r;
}
ll count(ll N) {
  if (N < 0) return 0;
  D = to_string(N), memset(memo, -1, sizeof memo);
  return go(0, 0, 1);
}
