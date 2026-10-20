vi euler(const vector<vector<pii>>& g, int m, int s) {
  vi bal(sz(g)), it(sz(g)), used(m), path, st{s};
  bal[s]++;
  while (!st.empty()) {
    int v = st.back();
    if (it[v] == sz(g[v])) {
      path.push_back(v), st.pop_back();
      continue;
    }
    auto [u, e] = g[v][it[v]++];
    if (used[e]) continue;
    used[e] = 1, bal[v]--, bal[u]++, st.push_back(u);
  }
  for (int b : bal) if (b < 0) return {};
  if (sz(path) != m + 1) return {};
  return {path.rbegin(), path.rend()};
}
