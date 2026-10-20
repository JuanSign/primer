map<vi, int> ids;
int treeHash(const vector<vi>& g, int v, int p) {
  vi c;
  for (int u : g[v])
    if (u != p) c.push_back(treeHash(g, u, v));
  sort(all(c));
  auto it = ids.find(c);
  if (it != ids.end()) return it->second;
  int k = sz(ids);
  return ids[c] = k;
}
