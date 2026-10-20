vi Z(const string& s) {
  vi z(sz(s));
  int l = -1, r = -1;
  rep(i, 1, sz(s)) {
    z[i] = i >= r ? 0 : min(r - i, z[i - l]);
    while (i + z[i] < sz(s) && s[i + z[i]] == s[z[i]]) z[i]++;
    if (i + z[i] > r) l = i, r = i + z[i];
  }
  return z;
}
