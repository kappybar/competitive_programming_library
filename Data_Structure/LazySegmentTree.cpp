#include <bits/stdc++.h>
#define rep(i,n) for(int i=0;i<(int)(n);i++)
using namespace std;
using ll = long long ;
using P = pair<int,int> ;
using pll = pair<long long,long long>;
constexpr int INF = 1e9;
constexpr long long LINF = 1e17;
constexpr int MOD = 1000000007;
constexpr double PI = 3.14159265358979323846;

/*
遅延評価付きセグメント木
f Mono * Mono -> Mono node配列のMonoを二つ作用させる関数。
g Mono * Ope -> Mono nodeにlazy配列を作用させる関数。
h Ope * Ope -> Ope　lazy配列の作用を結合させる関数。
tu Monoの単位元
eu Opeの単位元
f と hは掛け算のようなことができて、gは指数のようなことできればいい。
*/

template<typename Mono,typename Ope>
struct LazySegmentTree{
    using F = function<Mono(Mono,Mono)>;
    using G = function<Mono(Mono,Ope)>;
    using H = function<Ope(Ope,Ope)>;
    int n,height;
    F f; G g; H h; Mono tu; Ope eu;
    vector<Mono> node;
    vector<Ope> lazy;

    LazySegmentTree(F f,G g,H h,Mono tu,Ope eu):f(f),g(g),h(h),tu(tu),eu(eu){}

    void init(vector<Mono> v){
        int n_ = (int)(v.size());
        n = 1;height = 0;
        while(n < n_) n <<= 1,++ height;
        node.assign(2*n,tu);
        lazy.assign(2*n,eu);
        for(int i=0;i<n_;i++) node[i+n] = v[i];
        for(int i=n-1;i>0;i--) node[i] = f(node[i<<1],node[i<<1|1]);
    }

    Mono eval(int k){
        return (lazy[k]==eu)?node[k]:g(node[k],lazy[k]);
    }

    void prop(int k){
        if(lazy[k]==eu) return;
        lazy[k<<1] = h(lazy[k<<1],lazy[k]);
        lazy[k<<1|1] = h(lazy[k<<1|1],lazy[k]);
        node[k] = eval(k);
        lazy[k] = eu;
    }

    void prop_above(int k){
        for(int i=height;i>0;i--) prop(k>>i);
    }

    void recalc_above(int k){
        while(k>0){
            k >>= 1;
            node[k] = f(eval(k<<1),eval(k<<1|1));
        }
    }

    void set_val(int k,Mono x){
        k += n;
        prop_above(k);
        node[k] = x;
        lazy[k] = eu;
        recalc_above(k);
    }

    void update(int l,int r,Ope x){
        if(l >= r) return;
        l += n;r += n-1;
        prop_above(l);
        prop_above(r);
        int a = l,b = r;
        ++ r;
        while(l < r){
            if(l&1) lazy[l] = h(lazy[l],x), ++l;
            if(r&1) --r, lazy[r] = h(lazy[r],x);
            l >>= 1;r >>= 1;
        }
        recalc_above(a);
        recalc_above(b);
    }

    Mono query(int l,int r){
        if(l >= r) return tu;
        l += n;r += n-1;
        prop_above(l);
        prop_above(r);++r;
        Mono vl = tu,vr = tu;
        while(l < r){
            if(l&1) vl = f(vl,eval(l)), ++l;
            if(r&1) --r, vr = f(eval(r),vr);
            l >>= 1;r >>= 1;
        }
        return f(vl,vr);
    }
};

struct mono{
    ll two,one,zero;
};

int main(){
    auto f = [](mono l,mono r){
        l.two += r.two;
        l.one += r.one;
        l.zero += r.zero;
        return l;
    };
    auto g = [](mono l,ll x){
        l.two =  l.two + 2 * x * l.one + x * x * l.zero;
        l.one = l.one + x * l.zero;
        l.zero = l.zero;
        return l;
    };
    auto h = [](ll a,ll b){
        return a+b;
    };
    LazySegmentTree<mono,ll> seg(f,g,h,mono{0,0,0},0);

    int n;
    cin >> n;
    vector<mono> a(n);
    rep(i,n){
        ll b;cin >> b;
        a[i] = mono{b*b,b,1};
    }
    seg.init(a);

    int q;
    cin >> q;
    while(q--){
        int t;
        cin >> t;
        if(t==1){
            int l,r;
            ll x;
            cin >> l >> r >> x;
            --r;--l;
            seg.update(l,r+1,x);
        }else{
            int l,r;
            cin >> l >> r;
            --l;--r;
            cout << seg.query(l,r+1).two << endl;
        }
    }


    return 0;
}