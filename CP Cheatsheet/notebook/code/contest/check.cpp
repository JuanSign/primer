int main(int argc, char* argv[]) {
  ifstream in(argv[1]), out(argv[2]), ans(argv[3]);
  ll x, y; out >> x, ans >> y;
  if (x != y) return 1; // value must match brute
  // read in and out, return 1 if out is invalid
  return 0;
}
