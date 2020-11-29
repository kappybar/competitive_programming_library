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

//抽象化したセグメントツリー 

struct Segmenttree{
    using F = function<long long(long long,long long)>;
    F f;
    const long long unit;
    int n;
    vector<long long> node;

    Segmenttree(F f,long long unit,vector<long long> v):f(f),unit(unit){
        n = (int)(v.size());
        node.resize(2*n);
        for(int i=0;i<n;i++) node[i+n] = v[i];
        for(int i=n-1;i>=0;i--) node[i] = f(node[i<<1],node[i<<1|1]);
    }
    //i番目の要素をxに変更する
    void update(int i,long long x){
        i += n;
        node[i] = x;
        while(i>1){
            i >>= 1;
            node[i] = f(node[i<<1],node[i<<1|1]);
        }
    }
    //[l,r)の要素
    long long query(int l,int r){
        long long vl = unit,vr = unit;
        l += n; r += n;
        while(l<r){
            if(l&1) vl = f(vl,node[l++]);
            if(r&1) vr = f(vr,node[--r]);
            l >>= 1; r >>= 1;
        }
        return f(vl,vr);
    }
    //i番目の要素にアクセス
    long long getval(int i){
        return node[i+n];
    }
};

int main(){
    int n,q;
    cin >> n >> q;
    auto f = [](ll a,ll b){ return min(a,b);}; //関数
    ll unit = INT_MAX; //単位元
    Segmenttree seg(f,unit,vector<ll>(n,unit));

    while(q--){
        int t,x,y;
        cin >> t >> x >> y;
        if(t==0){
            seg.update(x,y);
        }else{
            cout << seg.query(x,y+1) << endl;
        }
    }
    return 0;
}