#include <bits/stdc++.h>

template <typename T>
struct BIT{
private:
    int n, len;
    std::vector<T> bit;

public:
    BIT(int n):n(n) {
        bit.assign(n+1, 0);
        len = 1;
        while ((len << 1) <= n) len <<= 1;
    }

private:
    // 1-index
    // sum of [1, i]
    T prefix_sum(int i) {
        T res = 0;
        while(i > 0) {
            res += bit[i];
            i -= i & -i;
        }
        return res;
    }

public:
    // 0-index
    // sum of [l, r)
    T sum(int l, int r) {
        // [0, r) - [0, l)
        return prefix_sum(r) - prefix_sum(l);
    }


    // 0-index
    // add val to a[i]
    void add(int i, T val) {
        i++;
        while(i <= n) {
            bit[i] += val;
            i += i & -i;
        }
        return;
    }

    // 0-index
    // constraints : \forall i a[i] >= 0
    // The smallest x that satisfies [a[0] + a[1] + ... + a[x] >= w]
    int lowerbound(T w) {
        if (w <= 0) return 0;
        int x = 0;
        for (int k = len;k > 0;k >>= 1) {
            if(x + k <= n && bit[x + k] < w){
                w -= bit[x + k];
                x += k;
            }
        }
        return x;
    }

    void debug(void) {
        std::cout << "sum[0:i] :"  << std::endl;
        for (int i = 0;i <= n; i++) {
            std::cout << sum(0, i) << " "; 
        }
        std::cout << std::endl;
        return;
    }
};
