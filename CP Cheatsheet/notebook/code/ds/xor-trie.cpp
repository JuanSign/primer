struct XorTrie {
  static const int B = 30;
  vector<array<int, 2>> nx{{0, 0}};
  vi cnt{0};
  void add(int x, int d = 1) {
    int v = 0;
    for (int i = B; i--;) {
      int b = x >> i & 1;
      if (!nx[v][b]) nx[v][b] = sz(nx), nx.push_back({0, 0}),
        cnt.push_back(0);
      v = nx[v][b], cnt[v] += d;
    }
  }
  int maxXor(int x) {
    int v = 0, r = 0;
    for (int i = B; i--;) {
      int b = !(x >> i & 1), u = nx[v][b];
      if (u && cnt[u]) r |= 1 << i, v = u;
      else v = nx[v][!b];
    }
    return r;
  }
};
