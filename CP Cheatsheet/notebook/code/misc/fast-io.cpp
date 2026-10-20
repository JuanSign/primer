char buf[1 << 16];
int bi, bn;
int gc() {
  if (bi == bn) bn = fread(buf, 1, sizeof buf, stdin), bi = 0;
  return bi < bn ? buf[bi++] : -1;
}
ll readInt() {
  int c = gc();
  while (c != '-' && (c < '0' || c > '9')) c = gc();
  bool neg = c == '-';
  if (neg) c = gc();
  ll x = 0;
  for (; c >= '0' && c <= '9'; c = gc()) x = x * 10 + c - '0';
  return neg ? -x : x;
}
