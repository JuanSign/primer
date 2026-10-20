void sosSub(vector<ll>& f, int B) {
  rep(b, 0, B) rep(m, 0, 1 << B) if (m >> b & 1)
    f[m] += f[m ^ 1 << b];
}
void sosSup(vector<ll>& f, int B) {
  rep(b, 0, B) rep(m, 0, 1 << B) if (!(m >> b & 1))
    f[m] += f[m | 1 << b];
}
