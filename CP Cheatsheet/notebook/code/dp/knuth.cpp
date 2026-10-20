ll knuth(int n, function<ll(int, int)> C) {
  vector<vector<ll>> dp(n + 1, vector<ll>(n + 1));
  vector<vi> opt(n + 1, vi(n + 1));
  rep(i, 0, n) opt[i][i + 1] = i + 1;
  rep(len, 2, n + 1) rep(i, 0, n - len + 1) {
    int j = i + len;
    dp[i][j] = LLONG_MAX;
    rep(k, opt[i][j - 1], min(opt[i + 1][j], j - 1) + 1) {
      ll v = dp[i][k] + dp[k][j] + C(i, j);
      if (v < dp[i][j]) dp[i][j] = v, opt[i][j] = k;
    }
  }
  return dp[0][n];
}
