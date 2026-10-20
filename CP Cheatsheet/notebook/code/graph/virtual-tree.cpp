vector<pii> virtualTree(LCA& L, vi v) {
  auto cmp = [&](int a, int b) { return L.tin[a] < L.tin[b]; };
  sort(all(v), cmp);
  int m = sz(v);
  rep(i, 0, m - 1) v.push_back(L.lca(v[i], v[i + 1]));
  sort(all(v), cmp), v.erase(unique(all(v)), v.end());
  vector<pii> r{{-1, v[0]}};
  rep(i, 1, sz(v)) r.push_back({L.lca(v[i - 1], v[i]), v[i]});
  return r;
}
