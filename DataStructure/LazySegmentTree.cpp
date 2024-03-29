#include <bits/stdc++.h>

template<typename S, S (*op)(S, S), S (*e)(), typename F, S (*mapping)(F, S), F (*composition)(F, F), F (*id)()>
struct LazySegmentTree {
private:
    int n, height;
    std::vector<S> node;
    std::vector<F> lazy;

public:
    LazySegmentTree(int n): LazySegmentTree(std::vector<S>(n, e())) {};
    LazySegmentTree(const std::vector<S> &v) {
        int vs = (int)v.size();
        n = 1;
        height = 0;
        while (n < vs) n <<= 1, height++;
        S es = e();
        node.assign(2*n, es);
        F ef = id();
        lazy.assign(2*n, ef);
        for (int i = 0;i < vs; i++) node[i + n] = v[i];
        for (int i = n - 1;i >= 0; i--) node[i] = op(node[i << 1], node[i << 1 | 1]);
        return;
    }

private:  
    S eval(int i) {
        return lazy[i] == id() ? node[i] : mapping(lazy[i], node[i]);
    }

    void propagate(int i) {
        if(lazy[i] == id()) return;
        lazy[i << 1] = composition(lazy[i << 1], lazy[i]);
        lazy[i << 1 | 1] = composition(lazy[i << 1 | 1], lazy[i]);
        node[i] = eval(i);
        lazy[i] = id();
        return;
    }

    void propagate_above(int i) {
        for(int j = height;j > 0; j--) propagate(i >> j);
        return;
    }

    void recalc_above(int i) {
        while(i > 0) {
            i >>= 1;
            node[i] = op(eval(i << 1), eval(i << 1 | 1));
        }
        return;
    }

public:
    // a[i] = x
    void set(int i, S x) {
        i += n;
        propagate_above(i);
        node[i] = x;
        lazy[i] = id();
        recalc_above(i);
        return;
    }

    // i \in [l, r) a[i] = mapping(x, a[i])
    void apply(int l, int r, F x) {
        if(l >= r) return;
        l += n;r += n - 1;
        propagate_above(l);
        propagate_above(r);
        int a = l, b = r;
        ++r;
        while(l < r) {
            if(l & 1) lazy[l] = composition(lazy[l], x), ++l;
            if(r & 1) --r, lazy[r] = composition(lazy[r], x);
            l >>= 1;r >>= 1;
        }
        recalc_above(a);
        recalc_above(b);
        return;
    }

    // op(a[l], a[l+1], ... a[r-1])
    S prod(int l, int r) {
        if(l >= r) return e();
        l += n;r += n-1;
        propagate_above(l);
        propagate_above(r);
        ++r;
        S vl = e(), vr = e();
        while(l < r) {
            if(l & 1) vl = op(vl, eval(l)), ++l;
            if(r & 1) --r, vr = op(eval(r), vr);
            l >>= 1;r >>= 1;
        }
        return op(vl, vr);
    }
};

// // RMQ, RUQ
// long long op(long long a, long long b) {
//     return std::min(a, b);
// }

// long long e() {
//     return (1LL << 31) - 1;
// }

// long long mapping(long long a, long long b) {
//     return a;
// }

// long long composition(long long a, long long b) {
//     return b;
// }

// long long id() {
//     return (1LL << 31) - 1;
// }


// // RMQ, RAQ
// long long op(long long a, long long b) {
//     return std::min(a, b);
// }

// long long e() {
//     return INF;
// }

// long long mapping(long long a, long long b) {
//     return b + a;
// }

// long long composition(long long a, long long b) {
//     return a + b;
// }

// long long id() {
//     return 0LL;
// }


// // RSQ, RAQ
// struct S {
//     long long sum, sz;
// };

// S op(S a, S b) {
//     return S{a.sum + b.sum, a.sz + b.sz};
// }

// S e() {
//     return S{0, 0};
// }

// S mapping(long long a, S b) {
//     return S{b.sum + a * b.sz, b.sz};
// }

// long long composition(long long a, long long b) {
//     return a + b;
// }

// long long id() {
//     return 0LL;
// }

// // RSQ, RUQ
// struct S {
//     long long sum, sz;
// };

// struct F {
//     long long x;
//     bool change;

//     bool operator == (const F& r) {
//         return x == r.x && change == r.change;
//     }
// };

// S op(S a, S b) {
//     return S{a.sum + b.sum, a.sz + b.sz};
// }

// S e() {
//     return S{0, 0};
// }

// S mapping(F a, S b) { 
//     return a.change ? S{a.x * b.sz, b.sz} : b;
// }

// F composition(F a, F b) {
//     return b;
// }

// F id() {
//     return F{0LL, false};
// }

