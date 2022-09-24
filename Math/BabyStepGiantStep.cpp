#include <bits/stdc++.h>

// return smalleset k s.t. x^k = y mod p
long long modlog(long long x, long long y, long long p) {
    if (y == 1) return 0;
    long long H = ceil(sqrt(p));
    std::vector<std::pair<long long, long long>> baby(H);
    for (long long b = 0, xby = y; b < H; b++, xby = (xby * x) % p) {
        baby[b] = std::make_pair(xby, b);
    }
    std::sort(baby.begin(), baby.end());
    long long xH = 1;
    for (int i = 0; i < H; ++i) {
        xH = (xH * x) % p;
    }
    for (long long a = 1, xaH = xH; a <= H; a++, xaH = (xaH * xH) % p) {
        auto it = std::lower_bound(baby.begin(), baby.end(), std::make_pair(xaH + 1, 0LL));
        if (it == baby.begin()) continue;
        it--;
        if (it->first == xaH) return a * H - it->second;
    }
    return -1;
}
