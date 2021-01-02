#include <bits/stdc++.h>
#define rep(i,n) for(int i=0;i<(int)(n);i++)
#define chmin(x,y) x = min((x),(y));
#define chmax(x,y) x = max((x),(y));
using namespace std;
using ll = long long ;
using P = pair<int,int> ;
using pll = pair<long long,long long>;
const int INF = 1e9;
const long long LINF = 1e17;
const int MOD = 1000000007;
//const int MOD = 998244353;
const double PI = 3.14159265358979323846;

struct Rollinghash{
    using bigint = __int128;
    int n;
    const bigint m = (1LL<<61)-1; //mod
    const bigint b = 1000000007;  //base ここはほ本当は乱択じゃないといけない
    vector<bigint> s;             //もともとの文字列(数列)
    vector<bigint> h;             //累積
    vector<bigint> pow_base;       // pow_base[i] = b^i
    Rollinghash(const string& str){      //文字列
        n = (int)str.size();
        s.resize(n);
        for(int i=0;i<n;i++) s[i] = str[i];
        init();
    }
    Rollinghash(const vector<int>& v){  //数列
        n = (int)v.size();
        s.resize(n);
        for(int i=0;i<n;i++) s[i] = v[i];
        init();
    }
    bigint mul(bigint a,bigint b){
        bigint c = a * b;
        c = (c >> 61) + (c & m);
        if(c >= m) c-= m;
        return c;
    }
    void init(){
        h.resize(n+1);
        h[0] = 0;
        pow_base.resize(n+1);
        pow_base[0] = 1;
        for(int i=1;i<=n;i++){
            pow_base[i] = mul( pow_base[i-1],b ) ;
        }
        for(int i=1;i<=n;i++){
            h[i] = mul(h[i-1],b) + s[i-1];
            if(h[i] >= m) h[i] -= m;
        }
    }
    //[l,r)
    long long hash(const int& l,const int& r){ 
        long long res = (long long)h[r];
        res -= mul(h[l], pow_base[r-l]);
        res = (res + m) % m;
        return res;
    }
}; 

int main(){
    int n;
    cin >> n;
    vector<int> a(2*n);
    vector<int> b(n);
    rep(i,n) cin >> a[i];
    rep(i,n) cin >> b[i];
    vector<int> ok(n,1);
    for(int k=0;k<30;k++){
        vector<int> a_(2*n);
        vector<int> b_(n);
        vector<int> b_rev(n);
        rep(i,n){
            a_[i] = (a[i]>>k)&1;
            a_[i+n] = a_[i];
            b_[i] = (b[i]>>k)&1;
            b_rev[i] = !b_[i];
        }
        Rollinghash ra(a_),rb(b_),rb_rev(b_rev);
        ll hash_b = rb.hash(0,n);
        ll hash_b_rev = rb_rev.hash(0,n);
        rep(i,n){
            if(ok[i]==0) continue;
            ll h = ra.hash(i,i+n);
            if(h != hash_b && h != hash_b_rev) ok[i] = 0;
        }
    }

    rep(i,n){
        if(ok[i]==1){
            cout << i << " ";
            cout << (b[0]^a[i]) << endl;
        }
    }

    return 0;
}

