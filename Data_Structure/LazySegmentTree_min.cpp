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


int main(){
    auto f = [](int a,int b){
        return min(a,b);
    };
    auto g = [](int a,int x){
        if(x==INT_MAX) return a;
        else return x;
    };
    auto h = [](int x,int y){
        if(y==-1) return x;
        else return y;
    };
    LazySegmentTree<int,int> seg(f,g,h,INT_MAX,-1);

    int n;
    cin >> n;
    vector<int> a(n,INT_MAX);
    seg.init(a);

    int q;
    cin >> q;
    while(q--){
        int t;
        cin >> t;
        if(t==0){
            int l,r,x;
            cin >> l >> r >> x;
            seg.update(l,r+1,x);
        }else{
            int l,r;
            cin >> l >> r;
            cout << seg.query(l,r+1) << endl;
        }
    }


    return 0;
}