#include <bits/stdc++.h>
#define rep(i,n) for(int i=0;i<(int)(n);i++)
#define chmin(x,y) x = min((x),(y))
#define chmax(x,y) x = max((x),(y))
#define popcount(x) __builtin_popcount(x)
using namespace std;
using ll = long long ;
using P = pair<int,int> ;
using pll = pair<long long,long long>;
const int INF = 1e9;
const long long LINF = 1e17;
const int MOD = 1000000007;
//const int MOD = 998244353;
const double PI = 3.14159265358979323846;

/* next combination */
int next_combination(int sub) {
    int x = sub & -sub, y = sub + x;
    return (((sub & ~y) / x) >> 1) | y;
}

int main(){
    int n,m;
    cin >> n >> m;
    vector<ll> dp(1<<n,0);
    dp[0] = 1;
    vector<vector<P>> cond(n+1);
    rep(i,m){
        int x,y,z;
        cin >> x >> y >> z;
        cond[x].emplace_back(y,z);
    }
    for(int i=1;i<=n;i++){
        for(int bit=(1<<i)-1;bit<(1<<n);bit = next_combination(bit)){
            bool ok = true;
            for(auto c:cond[i]){
                int y = c.first;
                int z = c.second;
                if(popcount(bit & ((1<<y) - 1)) > z) ok = false;
            }
            if(!ok){
                dp[bit] = 0;
                continue;
            }
            for(int j=0;j<n;j++){
                if(bit>>j&1){
                    dp[bit] += dp[bit^(1<<j)];
                }
            }
        }
    }
    cout << dp[(1<<n)-1] << endl;

    return 0;
}

//参考
//https://qiita.com/drken/items/7c6ff2aa4d8fce1c9361#next_combination