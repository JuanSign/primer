#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
for (int s = m; s; s = (s - 1) & m) {}  // submasks of m
int c = x & -x, r = x + c;  // next mask, same popcount
x = (((r ^ x) >> 2) / c) | r;
__builtin_popcountll(x), __builtin_ctzll(x), __lg(x);
string str(__int128 x) {
  if (x < 0) return "-" + str(-x);
  return (x >= 10 ? str(x / 10) : "") + char('0' + x % 10);
}
auto t0 = chrono::steady_clock::now();  // time limit check
double sec = chrono::duration<double>(
    chrono::steady_clock::now() - t0).count();
