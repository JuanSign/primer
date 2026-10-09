mt19937 mt(atoi(argv[1]));
auto rng = [&](int L, int R) {return L + int(mt() % (R - L + 1));};
