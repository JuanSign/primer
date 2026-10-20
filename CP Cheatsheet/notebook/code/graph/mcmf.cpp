struct MCMF {
  struct E { int to; ll cap, cost; };
  const ll INF = LLONG_MAX / 4;
  int n;
  vector<E> e;
  vector<vi> g;
  vector<ll> pot, d;
  vi pe;
  MCMF(int N) : n(N), g(N), pot(N), d(N), pe(N) {}
  void addEdge(int a, int b, ll cap, ll cost) {
    g[a].push_back(sz(e)), e.push_back({b, cap, cost});
    g[b].push_back(sz(e)), e.push_back({a, 0, -cost});
  }
  bool path(int s, int t) {
    fill(all(d), INF), d[s] = 0;
    priority_queue<pair<ll, int>> pq;
    pq.push({0, s});
    while (!pq.empty()) {
      auto [w, v] = pq.top();
      pq.pop();
      if (-w > d[v]) continue;
      for (int i : g[v]) {
        E& x = e[i];
        if (x.cap <= 0) continue;
        ll nd = d[v] + x.cost + pot[v] - pot[x.to];
        if (nd < d[x.to]) d[x.to] = nd, pe[x.to] = i,
          pq.push({-nd, x.to});
      }
    }
    return d[t] < INF;
  }
  pair<ll, ll> calc(int s, int t) {
    fill(all(pot), INF), pot[s] = 0;
    rep(it, 0, n) rep(i, 0, sz(e)) {
      int a = e[i ^ 1].to;
      if (e[i].cap > 0 && pot[a] < INF)
        pot[e[i].to] = min(pot[e[i].to], pot[a] + e[i].cost);
    }
    ll flow = 0, cost = 0;
    while (path(s, t)) {
      rep(v, 0, n) if (d[v] < INF) pot[v] += d[v];
      ll f = INF;
      for (int v = t; v != s; v = e[pe[v] ^ 1].to)
        f = min(f, e[pe[v]].cap);
      for (int v = t; v != s; v = e[pe[v] ^ 1].to)
        e[pe[v]].cap -= f, e[pe[v] ^ 1].cap += f;
      flow += f, cost += f * pot[t];
    }
    return {flow, cost};
  }
};
