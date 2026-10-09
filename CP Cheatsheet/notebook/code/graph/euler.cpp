// g[v] = {to, edge id}, m edges. Undirected: add both ways
// with one id. Returns the vertices of a path from s that uses
// every edge once, or {} if there is none. Start s at an odd
// vertex (undirected) or one with out = in + 1 (directed).
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
