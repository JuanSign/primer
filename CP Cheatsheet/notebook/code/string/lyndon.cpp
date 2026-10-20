vi duval(const string& s) {
  vi r;
  int n = sz(s), i = 0;
  while (i < n) {
    int j = i + 1, k = i;
    for (; j < n && s[k] <= s[j]; j++)
      k = s[k] < s[j] ? i : k + 1;
    while (i <= k) r.push_back(i), i += j - k;
  }
  return r;
}
int minRotation(string s) {
  int a = 0, n = sz(s);
  s += s;
  rep(b, 0, n) rep(k, 0, n) {
    if (a + k == b || s[a + k] < s[b + k]) {
      b += max(0, k - 1);
      break;
    }
    if (s[a + k] > s[b + k]) { a = b; break; }
  }
  return a;
}
