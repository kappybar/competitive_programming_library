#include <bits/stdc++.h>

template<typename T>
struct PotentialUnionfind{
private:
    int n;
    std::vector<int> parents;
    std::vector<T> weights;

public:
    PotentialUnionfind(int n):n(n), parents(n, -1), weights(n, 0) {}

    int find(int x) {
        if (parents[x] < 0) {
            return x;
        } else{
            int p = find(parents[x]);
            weights[x] += weights[parents[x]];
            return parents[x] = p;
        }
    }

private:
    // weight(x) = weight between x and root of x
    T weight(int x){
        find(x);
        return weights[x];
    }

public:
    // unite x and y under the condition that [weight[y] - weights[x] = w]
    bool unite(int x, int y, T w) {
        w += weight(x);
        w -= weight(y);
        x = find(x);
        y = find(y);
        if(x == y) return false;
        if(parents[x] > parents[y]) {
            std::swap(x,y); 
            w = -w;
        }
        parents[x] += parents[y];
        parents[y] = x;
        weights[y] = w;
        return true;
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }    

    // constraints : same(x, y) == true
    T diff(int x, int y) {
        return weight(y) - weight(x);
    }

};
