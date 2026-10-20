const int N = 1e7;
vi lp(N + 1), pr, phi(N + 1), mu(N + 1);
void sieve() {
  phi[1] = mu[1] = 1;
  rep(i, 2, N + 1) {
    if (!lp[i]) lp[i] = i, pr.push_back(i), phi[i] = i - 1,
      mu[i] = -1;
    for (int p : pr) {
      if (p > lp[i] || (ll)i * p > N) break;
      lp[i * p] = p;
      if (p == lp[i]) phi[i * p] = phi[i] * p;
      else phi[i * p] = phi[i] * (p - 1), mu[i * p] = -mu[i];
    }
  }
}
