#include <bits/stdc++.h>

struct Unionfind{
private:
    int n;
    std::vector<int> parents;

public:
    Unionfind(int n):n(n), parents(n,-1) {}

    int find(int x) {
        if(parents[x] < 0) return x;
        return parents[x] = find(parents[x]);
    }

    void unite(int x,int y) {
        x = find(x);
        y = find(y);

        if(x == y) return;
        if(parents[x] > parents[y]) std::swap(x, y);
        parents[x] += parents[y];
        parents[y] = x;
        return;
    }  

    int size(int x) {
        return -parents[find(x)];
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }

    std::vector<int> members(int x) {
        int root = find(x);
        std::vector<int> member;
        for(int i = 0;i < n; i++){
            if(find(i) == root ){
                member.push_back(i);
            }
        }
        return member;
    }

    int group_cnt(void) {
        int c = 0;
        for(int i = 0;i < n; i++){
            if(parents[i] < 0) ++c;
        }
        return c;
    }
};
