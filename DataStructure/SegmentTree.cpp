#include <bits/stdc++.h>

template <typename S, S (*op)(S, S), S (*e)()>
struct SegmentTree {
private:
    int n;
    std::vector<S> node;

public:
    SegmentTree(int n):SegmentTree(std::vector<S>(n, e()))  {}
    SegmentTree(const std::vector<S> &v) {
        n = (int)(v.size());
        node.resize(2*n);
        for(int i = 0;i < n; i++) node[i+n] = v[i];
        for(int i = n - 1;i >= 0; i--) node[i] = op(node[i << 1], node[i << 1 | 1]);
    }

    // a[i] = x
    void set(int i, S x) {
        i += n;
        node[i] = x;
        while(i > 1) {
            i >>= 1;
            node[i] = op(node[i << 1], node[i << 1 | 1]);
        }
        return;
    }

    // a[i]
    S get(int i) {
        return node[i + n];
    }

    // op(a[l], a[l+1], ... ,a[r-1])
    S query(int l, int r) {
        S vl = e(), vr = e();
        l += n; r += n;
        while(l < r) {
            if(l & 1) vl = op(vl, node[l++]);
            if(r & 1) vr = op(vr, node[--r]);
            l >>= 1; r >>= 1;
        }
        return op(vl, vr);
    }

};

// // min
// long long e() {
//     return (1LL << 31) - 1;
// }

// long long op(long long a, long long b) {
//     return std::min(a, b);
// }

// // sum
// long long e() {
//     return 0LL;
// }

// long long op(long long a, long long b) {
//     return a + b;
// }

// // max
// long long e() {
//     return 0LL;
// }

// long long op(long long a, long long b) {
//     return std::max(a, b);
// }
