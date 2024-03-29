#include <bits/stdc++.h>
const int inf = 1e9+10;

struct PartialPersistentUnionfind{
private:
    int n;
public:
    int now;
private:
    std::vector<int> par;
    std::vector<int> time;
    std::vector<std::vector<std::pair<int, int>>> sz;

public:
    PartialPersistentUnionfind(int n)
        :n(n),
         now(0),
         par(n, -1),
         time(n, inf),
         sz(n, std::vector<std::pair<int, int>>(1, {0,1})) {}

    // x's parent node when time is t
    int find(int x, int t) {
        if (t < time[x]) return x;
        return find(par[x], t);
    }

    // unite x, y
    // return now time
    int unite(int x, int y) {
        ++now;
        x = find(x, now);
        y = find(y, now);
        if (x == y) return now;
        if (par[x] > par[y]) std::swap(x, y);
        par[x] += par[y];
        par[y] = x;
        time[y] = now;
        sz[x].emplace_back(now, -par[x]);
        return now;
    }

    // size of x's group when time is t
    int size(int x, int t) {
        int p = find(x, t);
        int left = 0, right = (int)sz[p].size();
        while (right - left > 1) {
            int mid = (left + right) / 2;
            if (sz[p][mid].first <= t) left = mid;
            else right = mid;
        }
        return sz[p][left].second;
    }

    // return true if x and y belong to same group when time is t
    bool same(int x, int y, int t) {
        return find(x,t) == find(y,t);
    }
};
