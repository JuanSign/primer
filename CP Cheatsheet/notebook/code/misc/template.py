import sys
from math import gcd, isqrt, comb
from functools import lru_cache
sys.setrecursionlimit(1 << 25)
input = sys.stdin.readline
def ints(): return list(map(int, input().split()))
n, = ints()
a = ints()
print(sum(a) * pow(2, n, 10**9 + 7) % (10**9 + 7))
print(*a)
