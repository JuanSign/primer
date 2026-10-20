// occurrences: cnt = 1 on non-clones, then by decreasing
// len: cnt[link] += cnt. distinct = sum len - len[link]
struct SAM {
  struct St { int len, link; array<int, 26> nx; };
  vector<St> t{{0, -1, {}}};
  int last = 0;
  void add(char ch) {
    int c = ch - 'a', cur = sz(t), p = last;
    t.push_back({t[last].len + 1, 0, {}});
    for (; p >= 0 && !t[p].nx[c]; p = t[p].link)
      t[p].nx[c] = cur;
    if (p >= 0) {
      int q = t[p].nx[c];
      if (t[p].len + 1 == t[q].len) t[cur].link = q;
      else {
        int cl = sz(t);
        t.push_back({t[p].len + 1, t[q].link, t[q].nx});
        for (; p >= 0 && t[p].nx[c] == q; p = t[p].link)
          t[p].nx[c] = cl;
        t[q].link = t[cur].link = cl;
      }
    }
    last = cur;
  }
};
