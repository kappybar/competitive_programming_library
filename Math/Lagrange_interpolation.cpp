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

#include <atcoder/modint>
using namespace atcoder;

template<typename T>
vector<T> lagrange(vector<T> x,vector<T> y){
    int n = (int)x.size();
    vector<T> c(n,1);
    rep(i,n){
        rep(j,n){
            if(i==j) continue;
            c[i] *= (x[i]-x[j]);
        }
        c[i] = y[i] / c[i];
    }
    vector<T> dp(n+1,0);
    dp[0] = 1;
    rep(i,n){
        vector<T> dp_new(n+1,0);
        rep(j,n){
            if(j+1<n+1) dp_new[j+1] += dp[j];
            dp_new[j] -= x[i] * dp[j];
        }
        swap(dp,dp_new);
    }
    vector<T> res(n,0);
    rep(i,n){
        T now = 0;
        for(int j=n;j>0;j--){
            now += dp[j];
            res[j-1] += c[i]*now;
            now *= x[i];
        }
    }
    return res;
}

int main(){
    int p;
    cin >> p;
    modint::set_mod(p);
    vector<modint> a(p);
    rep(i,p){
        int aa;
        cin >> aa;
        a[i] = aa;
    }
    vector<modint> id(p);
    rep(i,p) id[i] = i;
    vector<modint> ans = lagrange(id,a);
    rep(i,p) cout << ans[i].val() << " ";
    cout << endl;
    return 0;
}